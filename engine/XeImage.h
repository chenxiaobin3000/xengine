/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-12- 1
 */

#ifndef _XEIMAGE_H_
#define _XEIMAGE_H_

namespace XE {

class CImage
{
public:
	CImage();
	virtual ~CImage();

	bool Load(const char* path);
	
	int GetWidth();

	int GetHeight();

	byte* GetBits();

private:
	int							m_nWidth;
	int							m_nHeight;
	byte*						m_pBits;
};

}

#endif //_XEIMAGE_H_
