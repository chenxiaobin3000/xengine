#include "stdafx.h"
#include "MyTexture.h"
#include "MyRenderManager.h"

namespace MyGUI {

	MyTexture::MyTexture(const std::string& _name) :
        mName(_name),
		mPixelFormat(0),
        mInternalPixelFormat(0),
        mUsage(0),
        mAccess(0),
        mNumElemBytes(0),
        mLock(false),
        mTexture(NULL) {
		
	}

	MyTexture::~MyTexture() {
		destroy();
	}

	const std::string& MyTexture::getName() const {
		return mName;
	}

	void MyTexture::createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format) {
		if (!mTexture) {
//			mTexture = new XE::CTexture;
//			if (!mTexture->Create()) {
//				delete mTexture;
//				mTexture = NULL;
//			}
		}
	}

	void MyTexture::destroy() {
		if (mTexture) {
			delete mTexture;
			mTexture = NULL;
		}
		
		mLock = false;
		mPixelFormat = 0;
		mUsage = 0;
		mInternalPixelFormat = 0;
		mAccess = 0;
		mNumElemBytes = 0;
		mOriginalFormat = PixelFormat::Unknow;
		mOriginalUsage = TextureUsage::Default;
	}

	void* MyTexture::lock(TextureUsage _access) {
		return NULL;
	}

	void MyTexture::unlock() {

	}

	void MyTexture::loadFromFile(const std::string& _filename) {
		destroy();
		
		if (!mTexture) {
			mTexture = new XE::CTexture;
			if (!mTexture->Load(_filename.c_str())) {
				delete mTexture;
				mTexture = NULL;
			}
		}
	}

	void MyTexture::saveToFile(const std::string& _filename) {

	}

	int MyTexture::getWidth() {
		if (mTexture) {
			return mTexture->GetWidth();
		} else {
			return 0;
		}
	}

	int MyTexture::getHeight() {
		if (mTexture) {
			return mTexture->GetHeight();
		} else {
			return 0;
		}
	}

	bool MyTexture::isLocked() {
		return mLock;
	}

	PixelFormat MyTexture::getFormat() {
		return mOriginalFormat;
	}

	TextureUsage MyTexture::getUsage() {
		return mOriginalUsage;
	}

	size_t MyTexture::getNumElemBytes() {
		return mNumElemBytes;
	}
    
    IRenderTarget* MyTexture::getRenderTarget() {
        return NULL;
    }

    int MyTexture::getTextureID() {
        if (mTexture) {
            return mTexture->GetTexture();
        } else {
            return 0;
        }
    }
    
} // namespace MyGUI
