/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XETEXTURE_H_
#define _XETEXTURE_H_

#include "XeRenderFormat.h"

namespace XE {

class ITexture;

class MYGUI_EXPORT ITextureInvalidateListener
{
public:
	virtual ~ITextureInvalidateListener() { }
	virtual void textureInvalidate(ITexture* _texture) = 0;
};
	
class ITexture
{
 public:
	virtual ITexture() {}
	
	virtual const std::string& getName() const = 0;

	virtual void createManual(int width, int height, EPixelFormat format) = 0;
	virtual void loadFromFile(const std::string& _filename) = 0;
	virtual void saveToFile(const std::string& _filename) = 0;

	virtual void setInvalidateListener(ITextureInvalidateListener* _listener) { }

	virtual void destroy() = 0;

	virtual void* lock() = 0;
	virtual void unlock() = 0;
	virtual bool isLocked() = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual PixelFormat getFormat() = 0;
};

#endif //_XETEXTURE_H_

