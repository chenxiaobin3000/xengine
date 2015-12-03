#include "stdafx.h"
#include "XeZipUtils.h"
#include "XeXFile.h"

#include <zlib.h>

unsigned int ZipUtils::s_uEncryptedPvrKeyParts[4] = {0,0,0,0};
unsigned int ZipUtils::s_uEncryptionKey[1024];
bool ZipUtils::s_bEncryptionKeyIsValid = false;

// --------------------- ZipUtils ---------------------

inline void ZipUtils::decodeEncodedPvr(unsigned int *data, ssize_t len)
{
    const int enclen = 1024;
    const int securelen = 512;
    const int distance = 64;
    
    // check if key was set
    // make sure to call caw_setkey_part() for all 4 key parts
    XEASSERT(s_uEncryptedPvrKeyParts[0] != 0);
    XEASSERT(s_uEncryptedPvrKeyParts[1] != 0);
    XEASSERT(s_uEncryptedPvrKeyParts[2] != 0);
    XEASSERT(s_uEncryptedPvrKeyParts[3] != 0);
    
    // create long key
    if(!s_bEncryptionKeyIsValid)
    {
        unsigned int y, p, e;
        unsigned int rounds = 6;
        unsigned int sum = 0;
        unsigned int z = s_uEncryptionKey[enclen-1];
        
        do
        {
#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (s_uEncryptedPvrKeyParts[(p&3)^e] ^ z)))
            
            sum += DELTA;
            e = (sum >> 2) & 3;
            
            for (p = 0; p < enclen - 1; p++)
            {
                y = s_uEncryptionKey[p + 1];
                z = s_uEncryptionKey[p] += MX;
            }
            
            y = s_uEncryptionKey[0];
            z = s_uEncryptionKey[enclen - 1] += MX;
            
        } while (--rounds);
        
        s_bEncryptionKeyIsValid = true;
    }
    
    int b = 0;
    int i = 0;
    
    // encrypt first part completely
    for(; i < len && i < securelen; i++)
    {
        data[i] ^= s_uEncryptionKey[b++];
        
        if(b >= enclen)
        {
            b = 0;
        }
    }
    
    // encrypt second section partially
    for(; i < len; i += distance)
    {
        data[i] ^= s_uEncryptionKey[b++];
        
        if(b >= enclen)
        {
            b = 0;
        }
    }
}

inline unsigned int ZipUtils::checksumPvr(const unsigned int *data, ssize_t len)
{
    unsigned int cs = 0;
    const int cslen = 128;
    
    len = (len < cslen) ? len : cslen;
    
    for(int i = 0; i < len; i++)
    {
        cs = cs ^ data[i];
    }
    
    return cs;
}

// memory in iPhone is precious
// Should buffer factor be 1.5 instead of 2 ?
#define BUFFER_INC_FACTOR (2)

int ZipUtils::inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t *outLength, ssize_t outLenghtHint)
{
    /* ret value */
    int err = Z_OK;
    
    ssize_t bufferSize = outLenghtHint;
    *out = (unsigned char*)malloc(bufferSize);
    
    z_stream d_stream; /* decompression stream */
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    
    d_stream.next_in  = in;
    d_stream.avail_in = static_cast<unsigned int>(inLength);
    d_stream.next_out = *out;
    d_stream.avail_out = static_cast<unsigned int>(bufferSize);
    
    /* window size to hold 256k */
    if( (err = inflateInit2(&d_stream, 15 + 32)) != Z_OK )
        return err;
    
    for (;;)
    {
        err = inflate(&d_stream, Z_NO_FLUSH);
        
        if (err == Z_STREAM_END)
        {
            break;
        }
        
        switch (err)
        {
            case Z_NEED_DICT:
                err = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&d_stream);
                return err;
        }
        
        // not enough memory ?
        if (err != Z_STREAM_END)
        {
            *out = (unsigned char*)realloc(*out, bufferSize * BUFFER_INC_FACTOR);
            
            /* not enough memory, ouch */
            if (! *out )
            {
                XELOG("cocos2d: ZipUtils: realloc failed");
                inflateEnd(&d_stream);
                return Z_MEM_ERROR;
            }
            
            d_stream.next_out = *out + bufferSize;
            d_stream.avail_out = static_cast<unsigned int>(bufferSize);
            bufferSize *= BUFFER_INC_FACTOR;
        }
    }
    
    *outLength = bufferSize - d_stream.avail_out;
    err = inflateEnd(&d_stream);
    return err;
}

ssize_t ZipUtils::inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint)
{
    ssize_t outLength = 0;
    int err = inflateMemoryWithHint(in, inLength, out, &outLength, outLengthHint);
    
    if (err != Z_OK || *out == nullptr) {
        if (err == Z_MEM_ERROR)
        {
            XELOG("cocos2d: ZipUtils: Out of memory while decompressing map data!");
        } else
            if (err == Z_VERSION_ERROR)
            {
                XELOG("cocos2d: ZipUtils: Incompatible zlib version!");
            } else
                if (err == Z_DATA_ERROR)
                {
                    XELOG("cocos2d: ZipUtils: Incorrect zlib compressed data!");
                }
                else
                {
                    XELOG("cocos2d: ZipUtils: Unknown error while decompressing map data!");
                }

        if(*out) {
            free(*out);
            *out = nullptr;
        }
        outLength = 0;
    }
    
    return outLength;
}

ssize_t ZipUtils::inflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out)
{
    // 256k for hint
    return inflateMemoryWithHint(in, inLength, out, 256 * 1024);
}

int ZipUtils::inflateGZipFile(const char *path, unsigned char **out)
{
    int len;
    unsigned int offset = 0;
    
    gzFile inFile = gzopen(path, "rb");
    if( inFile == nullptr ) {
        XELOG("cocos2d: ZipUtils: error open gzip file: %s", path);
        return -1;
    }
    
    /* 512k initial decompress buffer */
    unsigned int bufferSize = 512 * 1024;
    unsigned int totalBufferSize = bufferSize;
    
    *out = (unsigned char*)malloc( bufferSize );
    if( ! out )
    {
        XELOG("cocos2d: ZipUtils: out of memory");
        return -1;
    }
    
    for (;;) {
        len = gzread(inFile, *out + offset, bufferSize);
        if (len < 0)
        {
            XELOG("cocos2d: ZipUtils: error in gzread");
            free( *out );
            *out = nullptr;
            return -1;
        }
        if (len == 0)
        {
            break;
        }
        
        offset += len;
        
        // finish reading the file
        if( (unsigned int)len < bufferSize )
        {
            break;
        }
        
        bufferSize *= BUFFER_INC_FACTOR;
        totalBufferSize += bufferSize;
        unsigned char *tmp = (unsigned char*)realloc(*out, totalBufferSize );
        
        if( ! tmp )
        {
            XELOG("cocos2d: ZipUtils: out of memory");
            free( *out );
            *out = nullptr;
            return -1;
        }
        
        *out = tmp;
    }
    
    if (gzclose(inFile) != Z_OK)
    {
        XELOG("cocos2d: ZipUtils: gzclose failed");
    }
    
    return offset;
}

bool ZipUtils::isCCZFile(const char *path)
{
    // load file into memory
//    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);
//    if (compressedData.isNull())
//    {
//        XELOG("cocos2d: ZipUtils: loading file failed");
//        return false;
//    }
//    return isCCZBuffer(compressedData.getBytes(), compressedData.getSize());
    
    byte* buffer;
    unsigned int size;
    if (XE::CXFile::ReadFile(path, buffer, size)) {
        XELOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }

    bool bRet = isCCZBuffer(buffer, size);
    XEDELETE(buffer);
    return bRet;
}

bool ZipUtils::isCCZBuffer(const unsigned char *buffer, ssize_t len)
{
    if (static_cast<size_t>(len) < sizeof(struct CCZHeader))
    {
        return false;
    }
    
    struct CCZHeader *header = (struct CCZHeader*) buffer;
    return header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && (header->sig[3] == '!' || header->sig[3] == 'p');
}


bool ZipUtils::isGZipFile(const char *path)
{
    // load file into memory
//    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);
//    if (compressedData.isNull())
//    {
//        XELOG("cocos2d: ZipUtils: loading file failed");
//        return false;
//    }
//
//    return isGZipBuffer(compressedData.getBytes(), compressedData.getSize());
    
    byte* buffer;
    unsigned int size;
    if (XE::CXFile::ReadFile(path, buffer, size)) {
        XELOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }
    
    bool bRet = isGZipBuffer(buffer, size);
    XEDELETE(buffer);
    return bRet;
}

bool ZipUtils::isGZipBuffer(const unsigned char *buffer, ssize_t len)
{
    if (len < 2)
    {
        return false;
    }

    return buffer[0] == 0x1F && buffer[1] == 0x8B;
}


int ZipUtils::inflateCCZBuffer(const unsigned char *buffer, ssize_t bufferLen, unsigned char **out)
{
    struct CCZHeader *header = (struct CCZHeader*) buffer;

    // verify header
    if( header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == '!' )
    {
        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST( header->version );
        if( version > 2 )
        {
            XELOG("cocos2d: Unsupported CCZ header format");
            return -1;
        }

        // verify compression format
        if( CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB )
        {
            XELOG("cocos2d: CCZ Unsupported compression method");
            return -1;
        }
    }
    else if( header->sig[0] == 'C' && header->sig[1] == 'C' && header->sig[2] == 'Z' && header->sig[3] == 'p' )
    {
        // encrypted ccz file
        header = (struct CCZHeader*) buffer;

        // verify header version
        unsigned int version = CC_SWAP_INT16_BIG_TO_HOST( header->version );
        if( version > 0 )
        {
            XELOG("cocos2d: Unsupported CCZ header format");
            return -1;
        }

        // verify compression format
        if( CC_SWAP_INT16_BIG_TO_HOST(header->compression_type) != CCZ_COMPRESSION_ZLIB )
        {
            XELOG("cocos2d: CCZ Unsupported compression method");
            return -1;
        }

        // decrypt
        unsigned int* ints = (unsigned int*)(buffer+12);
        ssize_t enclen = (bufferLen-12)/4;

        decodeEncodedPvr(ints, enclen);

#if COCOS2D_DEBUG > 0
        // verify checksum in debug mode
        unsigned int calculated = checksumPvr(ints, enclen);
        unsigned int required = CC_SWAP_INT32_BIG_TO_HOST( header->reserved );

        if(calculated != required)
        {
            XELOG("cocos2d: Can't decrypt image file. Is the decryption key valid?");
            return -1;
        }
#endif
    }
    else
    {
        XELOG("cocos2d: Invalid CCZ file");
        return -1;
    }

    unsigned int len = CC_SWAP_INT32_BIG_TO_HOST( header->len );

    *out = (unsigned char*)malloc( len );
    if(! *out )
    {
        XELOG("cocos2d: CCZ: Failed to allocate memory for texture");
        return -1;
    }

    unsigned long destlen = len;
    size_t source = (size_t) buffer + sizeof(*header);
    int ret = uncompress(*out, &destlen, (Bytef*)source, bufferLen - sizeof(*header) );

    if( ret != Z_OK )
    {
        XELOG("cocos2d: CCZ: Failed to uncompress data");
        free( *out );
        *out = nullptr;
        return -1;
    }

    return len;
}

int ZipUtils::inflateCCZFile(const char *path, unsigned char **out)
{
    // load file into memory
//    Data compressedData = FileUtils::getInstance()->getDataFromFile(path);
//    if (compressedData.isNull())
//    {
//        XELOG("cocos2d: Error loading CCZ compressed file");
//        return -1;
//    }
//    
//    return inflateCCZBuffer(compressedData.getBytes(), compressedData.getSize(), out);
    
    byte* buffer;
    unsigned int size;
    if (XE::CXFile::ReadFile(path, buffer, size)) {
        XELOG("cocos2d: ZipUtils: loading file failed");
        return false;
    }
    
    bool bRet = inflateCCZBuffer(buffer, size, out);
    XEDELETE(buffer);
    return bRet;
}

void ZipUtils::setPvrEncryptionKeyPart(int index, unsigned int value)
{
    XEASSERT(index >= 0); // "Cocos2d: key part index cannot be less than 0"
    XEASSERT(index <= 3); // "Cocos2d: key part index cannot be greater than 3"
    
    if(s_uEncryptedPvrKeyParts[index] != value)
    {
        s_uEncryptedPvrKeyParts[index] = value;
        s_bEncryptionKeyIsValid = false;
    }
}

void ZipUtils::setPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4)
{
    setPvrEncryptionKeyPart(0, keyPart1);
    setPvrEncryptionKeyPart(1, keyPart2);
    setPvrEncryptionKeyPart(2, keyPart3);
    setPvrEncryptionKeyPart(3, keyPart4);
}
