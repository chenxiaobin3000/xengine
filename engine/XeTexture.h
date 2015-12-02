/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-27
 */

#ifndef _XE_TEXTURE_H_
#define _XE_TEXTURE_H_

#include "XeITexture.h"

namespace XE {

class CTexture : 
	public ITexture
{
public:
	CTexture();
	virtual ~CTexture();

	virtual bool Create(byte* rgb, int width, int height, EPixelFormat format);
	virtual bool Load(const char* path);
	virtual void Save(const char* path);

	virtual void Destroy();

	virtual void* Lock();
	virtual void UnLock();

	// 绑定纹理
	virtual void Bind();
	virtual void UnBind();

	virtual int GetWidth();
	virtual int GetHeight();
	virtual EPixelFormat GetFormat();
	
	void SetTexture(GLuint id);
	GLuint GetTexture();

private:
	GLuint						m_nTextureID;
	int							m_nWidth;
	int							m_nHeight;
};

}

#endif //_XE_TEXTURE_H_
