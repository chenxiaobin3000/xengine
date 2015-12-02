#include "stdafx.h"
#include "XeImage.h"

#import <UIKit/UIKit.h>

#define PVR_TEXTURE_FLAG_TYPE_MASK	0xff

static char gPVRTexIdentifier[5] = "PVR!";

enum {
    kPVRTextureFlagTypePVRTC_2 = 24,
    kPVRTextureFlagTypePVRTC_4
};

typedef struct _PVRTexHeader {
    uint32_t headerLength;
    uint32_t height;
    uint32_t width;
    uint32_t numMipmaps;
    uint32_t flags;
    uint32_t dataLength;
    uint32_t bpp;
    uint32_t bitmaskRed;
    uint32_t bitmaskGreen;
    uint32_t bitmaskBlue;
    uint32_t bitmaskAlpha;
    uint32_t pvrTag;
    uint32_t numSurfs;
} PVRTexHeader;

@interface PVRTexture : NSObject

@property(nonatomic, strong) NSMutableArray*     imageData;
@property(nonatomic, assign) uint32_t            width;
@property(nonatomic, assign) uint32_t            height;
@property(nonatomic, assign) GLenum              internalFormat;
@property(nonatomic, assign) BOOL                hasAlpha;

@end

@implementation PVRTexture

- (id)initWithFile:(NSString *)path {
    if (self = [super init]) {
        // 重定向到资源目录
        NSString* dir = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"res"];
        NSString* paths = [NSString stringWithFormat:@"%@/%@", dir, path];
        
        NSData *data = [NSData dataWithContentsOfFile:paths];
        if (!data) {
            self = nil;
            return self;
        }
        
        _imageData = [[NSMutableArray alloc] initWithCapacity:10];
        _width = _height = 0;
        _internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
        _hasAlpha = FALSE;
        if (![self unpackPVRData:data]) {
            self = nil;
        }
    }
    
    return self;
}

- (BOOL)unpackPVRData:(NSData *)data {
    BOOL success = FALSE;
    PVRTexHeader *header = NULL;
    uint32_t flags, pvrTag;
    uint32_t dataLength = 0, dataOffset = 0, dataSize = 0;
    uint32_t blockSize = 0, widthBlocks = 0, heightBlocks = 0;
    uint32_t width = 0, height = 0, bpp = 4;
    uint8_t *bytes = NULL;
    uint32_t formatFlags;
    
    header = (PVRTexHeader *)[data bytes];
    pvrTag = CFSwapInt32LittleToHost(header->pvrTag);
    if (gPVRTexIdentifier[0] != ((pvrTag >>  0) & 0xff) ||
        gPVRTexIdentifier[1] != ((pvrTag >>  8) & 0xff) ||
        gPVRTexIdentifier[2] != ((pvrTag >> 16) & 0xff) ||
        gPVRTexIdentifier[3] != ((pvrTag >> 24) & 0xff)) {
        return FALSE;
    }
    
    flags = CFSwapInt32LittleToHost(header->flags);
    formatFlags = flags & PVR_TEXTURE_FLAG_TYPE_MASK;
    if (formatFlags == kPVRTextureFlagTypePVRTC_4 || formatFlags == kPVRTextureFlagTypePVRTC_2) {
        [_imageData removeAllObjects];
        
        if (formatFlags == kPVRTextureFlagTypePVRTC_4) {
            _internalFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
        } else if (formatFlags == kPVRTextureFlagTypePVRTC_2) {
            _internalFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
        }
        
        _width = width = CFSwapInt32LittleToHost(header->width);
        _height = height = CFSwapInt32LittleToHost(header->height);
        
        if (CFSwapInt32LittleToHost(header->bitmaskAlpha)) {
            _hasAlpha = TRUE;
        } else {
            _hasAlpha = FALSE;
        }
        
        dataLength = CFSwapInt32LittleToHost(header->dataLength);
        bytes = ((uint8_t *)[data bytes]) + sizeof(PVRTexHeader);
        
        // Calculate the data size for each texture level and respect the minimum number of blocks
        while (dataOffset < dataLength) {
            if (formatFlags == kPVRTextureFlagTypePVRTC_4) {
                blockSize = 4 * 4; // Pixel by pixel block size for 4bpp
                widthBlocks = width / 4;
                heightBlocks = height / 4;
                bpp = 4;
            } else {
                blockSize = 8 * 4; // Pixel by pixel block size for 2bpp
                widthBlocks = width / 8;
                heightBlocks = height / 4;
                bpp = 2;
            }
            
            // Clamp to minimum number of blocks
            if (widthBlocks < 2) {
                widthBlocks = 2;
            }
            if (heightBlocks < 2) {
                heightBlocks = 2;
            }
            
            dataSize = widthBlocks * heightBlocks * ((blockSize  * bpp) / 8);
            [_imageData addObject:[NSData dataWithBytes:bytes+dataOffset length:dataSize]];
            
            dataOffset += dataSize;
            width = MAX(width >> 1, 1);
            height = MAX(height >> 1, 1);
        }
        
        success = TRUE;
    }
    
    return success;
}

@end

namespace XE {

CImage::CImage() : m_nWidth(0), m_nHeight(0), m_pBits(NULL) {
	
}

CImage::~CImage() {
    if (m_pBits) {
        XEDELETE(m_pBits);
    }
}

bool CImage::Load(const char* path) {
    NSString* nsPath = [NSString stringWithUTF8String:path];
    PVRTexture* pvr = [[PVRTexture alloc] initWithFile:nsPath];
    m_nWidth = pvr.width;
    m_nHeight = pvr.height;
    
    unsigned long size = [pvr.imageData count];
    if (m_pBits) {
        XEDELETE(m_pBits);
    }
    m_pBits = XENEW(byte[size]);
    if (!m_pBits) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        m_pBits[i] = [[pvr.imageData objectAtIndex:i] charValue];
    }
    
    return true;
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

}
