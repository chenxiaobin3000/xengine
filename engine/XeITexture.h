/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEITEXTURE_H_
#define _XEITEXTURE_H_

#include "XeRenderFormat.h"

namespace XE {

class ITexture;

class ITextureInvalidateListener
{
public:
	virtual ~ITextureInvalidateListener() {}
	
	virtual void onTextureInvalidate(ITexture* texture) = 0;
};

class ITexture
{
public:
	virtual ~ITexture() {}
	
	virtual const std::string& GetName() const = 0;

	virtual void Create(byte* rgb, int width, int height, EPixelFormat format) = 0;
	virtual void Load(const std::string& path) = 0;
	virtual void Save(const std::string& path) = 0;

	virtual void SetInvalidateListener(ITextureInvalidateListener* listener) { }

	virtual void Destroy() = 0;

	virtual void* Lock() = 0;
	virtual void UnLock() = 0;
	virtual bool IsLocked() = 0;

	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual PixelFormat GetFormat() = 0;
};

#endif //_XEITEXTURE_H_

