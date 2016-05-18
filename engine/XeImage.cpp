#include "stdafx.h"
#include "XeImage.h"
#include "XeXFile.h"
#include "XeZipUtils.h"

namespace XE {

static const int MIPMAP_MAX = 16;

static const int PVR_TEXTURE_FLAG_TYPE_MASK = 0xff;

// Values taken from PVRTexture.h from http://www.imgtec.com
enum class PVR2TextureFlag {
    Mipmap         = (1<<8),        // has mip map levels
    Twiddle        = (1<<9),        // is twiddled
    Bumpmap        = (1<<10),       // has normals encoded for a bump map
    Tiling         = (1<<11),       // is bordered for tiled pvr
    Cubemap        = (1<<12),       // is a cubemap/skybox
    FalseMipCol    = (1<<13),       // are there false colored MIP levels
    Volume         = (1<<14),       // is this a volume texture
    Alpha          = (1<<15),       // v2.1 is there transparency info in the texture
    VerticalFlip   = (1<<16),       // v2.1 is the texture vertically flipped
};

enum class PVR3TextureFlag {
    PremultipliedAlpha  = (1<<1)    // has premultiplied alpha
};

static const char gPVRTexIdentifier[5] = "PVR!";

// v2
enum class PVR2TexturePixelFormat : unsigned char {
    RGBA4444 = 0x10,
    RGBA5551,
    RGBA8888,
    RGB565,
    RGB555,          // unsupported
    RGB888,
    I8,
    AI88,
    PVRTC2BPP_RGBA,
    PVRTC4BPP_RGBA,
    BGRA8888,
    A8,
};
    
// v3
enum class PVR3TexturePixelFormat : uint64_t {
    PVRTC2BPP_RGB  = 0ULL,
    PVRTC2BPP_RGBA = 1ULL,
    PVRTC4BPP_RGB  = 2ULL,
    PVRTC4BPP_RGBA = 3ULL,
    PVRTC2_2BPP_RGBA = 4ULL,
    PVRTC2_4BPP_RGBA  = 5ULL,
    ETC1 = 6ULL,
    DXT1 = 7ULL,
    DXT2 = 8ULL,
    DXT3 = 9ULL,
    DXT4 = 10ULL,
    DXT5 = 11ULL,
    BC1 = 7ULL,
    BC2 = 9ULL,
    BC3 = 11ULL,
    BC4 = 12ULL,
    BC5 = 13ULL,
    BC6 = 14ULL,
    BC7 = 15ULL,
    UYVY = 16ULL,
    YUY2 = 17ULL,
    BW1bpp = 18ULL,
    R9G9B9E5 = 19ULL,
    RGBG8888 = 20ULL,
    GRGB8888 = 21ULL,
    ETC2_RGB = 22ULL,
    ETC2_RGBA = 23ULL,
    ETC2_RGBA1 = 24ULL,
    EAC_R11_Unsigned = 25ULL,
    EAC_R11_Signed = 26ULL,
    EAC_RG11_Unsigned = 27ULL,
    EAC_RG11_Signed = 28ULL,
    
    BGRA8888       = 0x0808080861726762ULL,
    RGBA8888       = 0x0808080861626772ULL,
    RGBA4444       = 0x0404040461626772ULL,
    RGBA5551       = 0x0105050561626772ULL,
    RGB565         = 0x0005060500626772ULL,
    RGB888         = 0x0008080800626772ULL,
    A8             = 0x0000000800000061ULL,
    L8             = 0x000000080000006cULL,
    LA88           = 0x000008080000616cULL,
};

typedef struct _PVRTexHeader {
    unsigned int headerLength;
    unsigned int height;
    unsigned int width;
    unsigned int numMipmaps;
    unsigned int flags;
    unsigned int dataLength;
    unsigned int bpp;
    unsigned int bitmaskRed;
    unsigned int bitmaskGreen;
    unsigned int bitmaskBlue;
    unsigned int bitmaskAlpha;
    unsigned int pvrTag;
    unsigned int numSurfs;
} PVRv2TexHeader;
    
#ifdef _MSC_VER
#pragma pack(push,1)
#endif
typedef struct {
    uint32_t version;
    uint32_t flags;
    uint64_t pixelFormat;
    uint32_t colorSpace;
    uint32_t channelType;
    uint32_t height;
    uint32_t width;
    uint32_t depth;
    uint32_t numberOfSurfaces;
    uint32_t numberOfFaces;
    uint32_t numberOfMipmaps;
    uint32_t metadataLength;
#ifdef _MSC_VER
} PVRv3TexHeader;
#pragma pack(pop)
#else
} __attribute__((packed)) PVRv3TexHeader;
#endif

//pvr structure end

CImage::CImage() : m_eFormat(EImageFormatUnknown),
				   m_nWidth(0),
				   m_nHeight(0),
				   m_pBits(NULL) {
	
}

CImage::~CImage() {
    if (m_pBits) {
        XEDELETE(m_pBits);
    }
}

bool CImage::Load(const char* path) {
    std::string str = "texture/";
    str += path;
	
	byte* buffer;
	unsigned int size;
	if (!CXFile::ReadFile(str.c_str(), buffer, size)) {
		return false;
	}
        
	unsigned char* unpackedData = NULL;
	ssize_t unpackedLen = 0;
	
	//detect and unzip the compress file
	if (ZipUtils::isCCZBuffer(buffer, size)) {
		unpackedLen = ZipUtils::inflateCCZBuffer(buffer, size, &unpackedData);
	} else if (ZipUtils::isGZipBuffer(buffer, size)) {
		unpackedLen = ZipUtils::inflateMemory(buffer, size, &unpackedData);
	} else {
		unpackedData = buffer;
		unpackedLen = size;
	}
	
    bool bRet = false;
	m_eFormat = DetectFormat(unpackedData, unpackedLen);
	switch (m_eFormat) {
	case EImageFormatPvr:
		bRet = InitWithPVRData(unpackedData, unpackedLen);
		break;
	case EImageFormatEtc:
		bRet = InitWithETCData(unpackedData, unpackedLen);
		break;
	default:
		break;
	}
   
	if (unpackedData != buffer) {
		XEDELETE(unpackedData);
	}
	XEDELETE(buffer);

    return bRet;
}

EImageFormat CImage::GetFormat() {
    return m_eFormat;
}

int CImage::GetWidth() {
    return m_nWidth;
}

int CImage::GetHeight() {
    return m_nHeight;
}

byte* CImage::GetBits() {
    return m_pBits;
}

EImageFormat CImage::DetectFormat(const unsigned char* buffer, ssize_t size) {
    if (IsPvr(buffer, size)) {
        return EImageFormatPvr;
    } else if (IsEtc(buffer, size)) {
        return EImageFormatEtc;
    } else {
        return EImageFormatUnknown;
    }
}

bool CImage::IsPvr(const unsigned char* buffer, ssize_t size) {
    if (static_cast<size_t>(size) < sizeof(PVRv2TexHeader)
	||  static_cast<size_t>(size) < sizeof(PVRv3TexHeader)) {
        return false;
    }
    
    const PVRv2TexHeader* headerv2 = static_cast<const PVRv2TexHeader*>(static_cast<const void*>(buffer));
    const PVRv3TexHeader* headerv3 = static_cast<const PVRv3TexHeader*>(static_cast<const void*>(buffer));
    
    return memcmp(&headerv2->pvrTag, gPVRTexIdentifier, strlen(gPVRTexIdentifier)) == 0 || CC_SWAP_INT32_BIG_TO_HOST(headerv3->version) == 0x50565203;
}

bool CImage::IsEtc(const unsigned char* buffer, ssize_t size) {
    //return etc1_pkm_is_valid((etc1_byte*)buffer) ? true : false;
	return false;
}

bool CImage::InitWithPVRData(const unsigned char* buffer, ssize_t size) {
    return InitWithPVRv2Data(buffer, size) || InitWithPVRv3Data(buffer, size);
}

bool CImage::InitWithPVRv2Data(const unsigned char* buffer, ssize_t size) {
    int dataLength = 0, dataOffset = 0, dataSize = 0;
    int blockSize = 0, widthBlocks = 0, heightBlocks = 0;
    int width = 0, height = 0;
    
    //Cast first sizeof(PVRTexHeader) bytes of data stream as PVRTexHeader
    const PVRv2TexHeader *header = static_cast<const PVRv2TexHeader *>(static_cast<const void*>(buffer));
    
    //Make sure that tag is in correct formatting
    if (memcmp(&header->pvrTag, gPVRTexIdentifier, strlen(gPVRTexIdentifier)) != 0) {
        return false;
    }
    
    unsigned int flags = CC_SWAP_INT32_LITTLE_TO_HOST(header->flags);
    PVR2TexturePixelFormat formatFlags = static_cast<PVR2TexturePixelFormat>(flags & PVR_TEXTURE_FLAG_TYPE_MASK);
    bool flipped = (flags & (unsigned int)PVR2TextureFlag::VerticalFlip) ? true : false;
    if (flipped) {
        XELOG("WARNING: Image is flipped. Regenerate it using PVRTexTool");
    }

    //Reset num of mipmaps
    int _numberOfMipmaps = 0;
    
    //Get size of mipmap
    m_nWidth = width = CC_SWAP_INT32_LITTLE_TO_HOST(header->width);
    m_nHeight = height = CC_SWAP_INT32_LITTLE_TO_HOST(header->height);
    
    //Get ptr to where data starts..
    dataLength = CC_SWAP_INT32_LITTLE_TO_HOST(header->dataLength);
    
    //Move by size of header
    size_t _dataLen = size - sizeof(PVRv2TexHeader);
    m_pBits = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
    memcpy(m_pBits, (unsigned char*)buffer + sizeof(PVRv2TexHeader), _dataLen);
    
    int bpp = 8;
    
    // Calculate the data size for each texture level and respect the minimum number of blocks
    while (dataOffset < dataLength) {
        switch (formatFlags) {
		case PVR2TexturePixelFormat::PVRTC2BPP_RGBA:
			blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
			widthBlocks = width / 8;
			heightBlocks = height / 4;
            bpp = 2;
			break;
		case PVR2TexturePixelFormat::PVRTC4BPP_RGBA:
			blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
			widthBlocks = width / 4;
			heightBlocks = height / 4;
            bpp = 4;
			break;
		default:
			blockSize = 1;
			widthBlocks = width;
			heightBlocks = height;
			break;
        }
        
        // Clamp to minimum number of blocks
        if (widthBlocks < 2) {
            widthBlocks = 2;
        }
        if (heightBlocks < 2) {
            heightBlocks = 2;
        }
        
        dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
        int packetLength = (dataLength - dataOffset);
        packetLength = packetLength > dataSize ? dataSize : packetLength;
        
        _numberOfMipmaps++;
        
        dataOffset += packetLength;
        
        //Update width and height to the next lower power of two
        width = MAX(width >> 1, 1);
        height = MAX(height >> 1, 1);
    }
    
    return true;
}

bool CImage::InitWithPVRv3Data(const unsigned char* buffer, ssize_t size) {
    if (static_cast<size_t>(size) < sizeof(PVRv3TexHeader)) {
        return false;
    }
    
    const PVRv3TexHeader *header = static_cast<const PVRv3TexHeader *>(static_cast<const void*>(buffer));
    
    // validate version
    if (CC_SWAP_INT32_BIG_TO_HOST(header->version) != 0x50565203) {
        XELOG("WARNING: pvr file version mismatch");
        return false;
    }
    
    PVR3TexturePixelFormat pixelFormat = static_cast<PVR3TexturePixelFormat>(header->pixelFormat);
    
    int bpp = 8;
    
    // sizing
    int width = CC_SWAP_INT32_LITTLE_TO_HOST(header->width);
    int height = CC_SWAP_INT32_LITTLE_TO_HOST(header->height);
    m_nWidth = width;
    m_nHeight = height;
    int dataOffset = 0, dataSize = 0;
    int blockSize = 0, widthBlocks = 0, heightBlocks = 0;
    
    size_t _dataLen = size - (sizeof(PVRv3TexHeader) + header->metadataLength);
    m_pBits = static_cast<unsigned char*>(malloc(_dataLen * sizeof(unsigned char)));
    memcpy(m_pBits, static_cast<const unsigned char*>(buffer) + sizeof(PVRv3TexHeader) + header->metadataLength, _dataLen);
    
    int _numberOfMipmaps = header->numberOfMipmaps;
    XEASSERT(_numberOfMipmaps < MIPMAP_MAX);
    
    for (int i = 0; i < _numberOfMipmaps; i++) {
        switch ((PVR3TexturePixelFormat)pixelFormat) {
		case PVR3TexturePixelFormat::PVRTC2BPP_RGB :
		case PVR3TexturePixelFormat::PVRTC2BPP_RGBA :
			blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
			widthBlocks = width / 8;
			heightBlocks = height / 4;
            bpp = 2;
			break;
		case PVR3TexturePixelFormat::PVRTC4BPP_RGB :
		case PVR3TexturePixelFormat::PVRTC4BPP_RGBA :
			blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
			widthBlocks = width / 4;
			heightBlocks = height / 4;
            bpp = 4;
			break;
		case PVR3TexturePixelFormat::ETC1:
			blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
			widthBlocks = width / 4;
			heightBlocks = height / 4;
            bpp = 4;
			break;
		default:
			blockSize = 1;
			widthBlocks = width;
			heightBlocks = height;
			break;
        }
        
        // Clamp to minimum number of blocks
        if (widthBlocks < 2) {
            widthBlocks = 2;
        }
        if (heightBlocks < 2) {
            heightBlocks = 2;
        }
        
        dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
        auto packetLength = _dataLen - dataOffset;
        packetLength = packetLength > dataSize ? dataSize : packetLength;

        dataOffset += packetLength;
        XEASSERT(dataOffset <= _dataLen);
        
        width = MAX(width >> 1, 1);
        height = MAX(height >> 1, 1);
    }

    return true;
}

bool CImage::InitWithETCData(const unsigned char* buffer, ssize_t size) {
	return false;
}

}
