/**
 * desc: 引入cocos的zip类，支持ccz压缩
 * auth: chenxiaobin
 * data: 2015-12- 3
 */

#ifndef _XEZIPUTILS_H_
#define _XEZIPUTILS_H_

#define CC_HOST_IS_BIG_ENDIAN (bool)(*(unsigned short *)"\0\xff" < 0x100)
#define CC_SWAP32(i)  ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define CC_SWAP16(i)  ((i & 0x00ff) << 8 | (i &0xff00) >> 8)
#define CC_SWAP_INT32_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true)? CC_SWAP32(i) : (i) )
#define CC_SWAP_INT16_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true)? CC_SWAP16(i) : (i) )
#define CC_SWAP_INT32_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true)? (i) : CC_SWAP32(i) )
#define CC_SWAP_INT16_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true)? (i):  CC_SWAP16(i) )

#ifndef _unz64_H
typedef struct unz_file_info_s unz_file_info;
#endif

/** XXX: pragma pack ???
 * @struct CCZHeader
 */
struct CCZHeader {
    unsigned char   sig[4];             /** Signature. Should be 'CCZ!' 4 bytes. */
    unsigned short  compression_type;   /** Should be 0. */
    unsigned short  version;            /** Should be 2 (although version type==1 is also supported). */
    unsigned int    reserved;           /** Reserved for users. */
    unsigned int    len;                /** Size of the uncompressed file. */
};

enum {
    CCZ_COMPRESSION_ZLIB,               /** zlib format. */
    CCZ_COMPRESSION_BZIP2,              /** bzip2 format (not supported yet). */
    CCZ_COMPRESSION_GZIP,               /** gzip format (not supported yet). */
    CCZ_COMPRESSION_NONE,               /** plain (not supported yet). */
};

class ZipUtils
{
public:
    /**
     * Inflates either zlib or gzip deflated memory. The inflated memory is expected to be freed by the caller.
     *
     * It will allocate 256k for the destination buffer. If it is not enough it will multiply the previous buffer size per 2, until there is enough memory.
     *
     * @return The length of the deflated buffer.
     * @since v0.8.1
     */
    static ssize_t ccInflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out) { return inflateMemory(in, inLength, out); }
    static ssize_t inflateMemory(unsigned char *in, ssize_t inLength, unsigned char **out);
    
    /**
     * Inflates either zlib or gzip deflated memory. The inflated memory is expected to be freed by the caller.
     *
     * @param outLenghtHint It is assumed to be the needed room to allocate the inflated buffer.
     *
     * @return The length of the deflated buffer.
     * @since v1.0.0
     */
    static ssize_t ccInflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint) { return inflateMemoryWithHint(in, inLength, out, outLengthHint); }
    static ssize_t inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t outLengthHint);
    
    /**
     * Inflates a GZip file into memory.
     *
     * @return The length of the deflated buffer.
     * @since v0.99.5
     */
    static int ccInflateGZipFile(const char *filename, unsigned char **out) { return inflateGZipFile(filename, out); }
    static int inflateGZipFile(const char *filename, unsigned char **out);
    
    /**
     * Test a file is a GZip format file or not.
     *
     * @return True is a GZip format file. false is not.
     * @since v3.0
     */
    static bool ccIsGZipFile(const char *filename) { return isGZipFile(filename); }
    static bool isGZipFile(const char *filename);
    
    /**
     * Test the buffer is GZip format or not.
     *
     * @return True is GZip format. false is not.
     * @since v3.0
     */
    static bool ccIsGZipBuffer(const unsigned char *buffer, ssize_t len) { return isGZipBuffer(buffer, len); }
    static bool isGZipBuffer(const unsigned char *buffer, ssize_t len);
    
    /**
     * Inflates a CCZ file into memory.
     *
     * @return The length of the deflated buffer.
     * @since v0.99.5
     */
    static int ccInflateCCZFile(const char *filename, unsigned char **out) { return inflateCCZFile(filename, out); }
    static int inflateCCZFile(const char *filename, unsigned char **out);
    
    /**
     * Inflates a buffer with CCZ format into memory.
     *
     * @return The length of the deflated buffer.
     * @since v3.0
     */
    static int ccInflateCCZBuffer(const unsigned char *buffer, ssize_t len, unsigned char **out) { return inflateCCZBuffer(buffer, len, out); }
    static int inflateCCZBuffer(const unsigned char *buffer, ssize_t len, unsigned char **out);
    
    /**
     * Test a file is a CCZ format file or not.
     *
     * @return True is a CCZ format file. false is not.
     * @since v3.0
     */
    static bool ccIsCCZFile(const char *filename) { return isCCZFile(filename); }
    static bool isCCZFile(const char *filename);
    
    /**
     * Test the buffer is CCZ format or not.
     *
     * @return True is CCZ format. false is not.
     * @since v3.0
     */
    static bool ccIsCCZBuffer(const unsigned char *buffer, ssize_t len) { return isCCZBuffer(buffer, len); }
    static bool isCCZBuffer(const unsigned char *buffer, ssize_t len);
    
    /**
     * Sets the pvr.ccz encryption key parts separately for added security.
     *
     * Example: If the key used to encrypt the pvr.ccz file is
     * 0xaaaaaaaabbbbbbbbccccccccdddddddd you will call this function 4
     * different times, preferably from 4 different source files, as follows
     *
     * ZipUtils::setPvrEncryptionKeyPart(0, 0xaaaaaaaa);
     * ZipUtils::setPvrEncryptionKeyPart(1, 0xbbbbbbbb);
     * ZipUtils::setPvrEncryptionKeyPart(2, 0xcccccccc);
     * ZipUtils::setPvrEncryptionKeyPart(3, 0xdddddddd);
     *
     * Splitting the key into 4 parts and calling the function from 4 different source
     * files increases the difficulty to reverse engineer the encryption key.
     * Be aware that encrpytion is *never* 100% secure and the key code
     * can be cracked by knowledgable persons.
     *
     * IMPORTANT: Be sure to call setPvrEncryptionKey or
     * setPvrEncryptionKeyPart with all of the key parts *before* loading
     * the sprite sheet or decryption will fail and the sprite sheet
     * will fail to load.
     *
     * @param index Part of the key [0..3].
     * @param value Value of the key part.
     */
    static void ccSetPvrEncryptionKeyPart(int index, unsigned int value) { setPvrEncryptionKeyPart(index, value); }
    static void setPvrEncryptionKeyPart(int index, unsigned int value);
    
    /**
     * Sets the pvr.ccz encryption key.
     *
     * Example: If the key used to encrypt the pvr.ccz file is
     * 0xaaaaaaaabbbbbbbbccccccccdddddddd you will call this function with
     * the key split into 4 parts as follows
     *
     * ZipUtils::setPvrEncryptionKey(0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd);
     *
     * Note that using this function makes it easier to reverse engineer and discover
     * the complete key because the key parts are present in one function call.
     *
     * IMPORTANT: Be sure to call setPvrEncryptionKey or setPvrEncryptionKeyPart
     * with all of the key parts *before* loading the spritesheet or decryption
     * will fail and the sprite sheet will fail to load.
     *
     * @param keyPart1 The key value part 1.
     * @param keyPart2 The key value part 2.
     * @param keyPart3 The key value part 3.
     * @param keyPart4 The key value part 4.
     */
    static void ccSetPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4) { setPvrEncryptionKey(keyPart1, keyPart2, keyPart3, keyPart4); }
    static void setPvrEncryptionKey(unsigned int keyPart1, unsigned int keyPart2, unsigned int keyPart3, unsigned int keyPart4);
    
private:
    static int inflateMemoryWithHint(unsigned char *in, ssize_t inLength, unsigned char **out, ssize_t *outLength, ssize_t outLenghtHint);
    static inline void decodeEncodedPvr (unsigned int *data, ssize_t len);
    static inline unsigned int checksumPvr(const unsigned int *data, ssize_t len);
    
    static unsigned int s_uEncryptedPvrKeyParts[4];
    static unsigned int s_uEncryptionKey[1024];
    static bool s_bEncryptionKeyIsValid;
};

#endif //_XEZIPUTILS_H_
