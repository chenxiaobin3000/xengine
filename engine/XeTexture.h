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

	// 绑定纹理
	virtual void Bind(int id);

	virtual void UnBind(int id);

/*	virtual bool LoadRGB(byte* rgb, int width, int height);

	virtual bool Deserialize(const char* path, const char* szLocalPath);

	virtual void Save(const char* path);

	void SetTexture(GLuint id);

	GLuint GetTexture();
*/
private:
	GLuint						m_nTextureID;
	int							m_nWidth;
	int							m_nHeight;
};

}

#endif //_XE_TEXTURE_H_
