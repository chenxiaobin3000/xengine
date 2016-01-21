/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-01- 6
 */

#ifndef _MY_TEXTURE_H_
#define _MY_TEXTURE_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_ITexture.h"
#include "MyGUI_RenderFormat.h"
#include "XeTexture.h"

namespace MyGUI {

	class MyTexture : public ITexture
	{
	public:
		MyTexture(const std::string& _name);
		virtual ~MyTexture();

		virtual const std::string& getName() const;

		virtual void createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format);
		virtual void loadFromFile(const std::string& _filename);
		virtual void saveToFile(const std::string& _filename);

		virtual void destroy();

		virtual int getWidth();
		virtual int getHeight();

		virtual void* lock(TextureUsage _access);
		virtual void unlock();
		virtual bool isLocked();

		virtual PixelFormat getFormat();
		virtual TextureUsage getUsage();
		virtual size_t getNumElemBytes();

		virtual IRenderTarget* getRenderTarget();

        int getTextureID();
        
	private:
		std::string mName;
		int mPixelFormat;
		int mInternalPixelFormat;
		int mUsage;
		int mAccess;
		size_t mNumElemBytes;
		bool mLock;
		PixelFormat mOriginalFormat;
		TextureUsage mOriginalUsage;
		XE::CTexture* mTexture;
	};

} // namespace MyGUI

#endif // _MY_TEXTURE_H_
