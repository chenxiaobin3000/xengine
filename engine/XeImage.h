/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-12- 1
 */

#ifndef _XEIMAGE_H_
#define _XEIMAGE_H_

#include "XeITexture.h"

namespace XE {

class CImage
{
public:
	CImage();
	virtual ~CImage();

	bool Load(const char* path);
	
    EImageFormat GetFormat();
    
	int GetWidth();

	int GetHeight();

	byte* GetBits();

private:
	EImageFormat DetectFormat(const unsigned char* buffer, ssize_t size);

	bool IsPvr(const unsigned char* buffer, ssize_t size);

	bool IsEtc(const unsigned char* buffer, ssize_t size);

	bool InitWithPVRData(const unsigned char* buffer, ssize_t size);

	bool InitWithPVRv2Data(const unsigned char* buffer, ssize_t size);

	bool InitWithPVRv3Data(const unsigned char* buffer, ssize_t size);

	bool InitWithETCData(const unsigned char* buffer, ssize_t size);
	
private:
	EImageFormat				m_eFormat;
	int							m_nWidth;
	int							m_nHeight;
	byte*						m_pBits;
};

}

#endif //_XEIMAGE_H_
