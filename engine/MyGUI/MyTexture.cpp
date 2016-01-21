#include "stdafx.h"
#include "MyTexture.h"
#include "MyRenderManager.h"
#include "MyRTTexture.h"
#include "XeImage.h"

namespace MyGUI {

	MyTexture::MyTexture(const std::string& _name) :
		mName(_name),
		mTextureID(0),
		mPboID(0),
		mWidth(0),
		mHeight(0),
		mLock(false),
		mPixelFormat(0),
		mDataSize(0),
		mUsage(0),
		mBuffer(0),
		mInternalPixelFormat(0),
		mAccess(0),
		mNumElemBytes(0),
		mRenderTarget(nullptr) {
		
	}

	MyTexture::~MyTexture() {
		destroy();
	}

	const std::string& MyTexture::getName() const {
		return mName;
	}

	void MyTexture::setUsage(TextureUsage _usage) {
		mAccess = 0;
		mUsage = 0;
	}

	void MyTexture::createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format) {
		createManual(_width, _height, _usage, _format, 0);
	}

	void MyTexture::createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format, void* _data) {
		mInternalPixelFormat = 0;
		mPixelFormat = 0;
		mNumElemBytes = 0;
		if (_format == PixelFormat::L8) {
			mInternalPixelFormat = GL_LUMINANCE;
			mPixelFormat = GL_LUMINANCE;
			mNumElemBytes = 1;
		} else if (_format == PixelFormat::L8A8) {
			mInternalPixelFormat = GL_LUMINANCE_ALPHA;
			mPixelFormat = GL_LUMINANCE_ALPHA;
			mNumElemBytes = 2;
		} else if (_format == PixelFormat::R8G8B8) {
			mInternalPixelFormat = GL_RGB;
			mPixelFormat = GL_RGB;
			mNumElemBytes = 3;
		} else if (_format == PixelFormat::R8G8B8A8) {
			mInternalPixelFormat = GL_RGBA;
			mPixelFormat = GL_RGBA;
			mNumElemBytes = 4;
		} else {

		}

		mWidth = _width;
		mHeight = _height;
		mDataSize = _width * _height * mNumElemBytes;
		setUsage(_usage);

		mOriginalFormat = _format;
		mOriginalUsage = _usage;

		int alignment = 0;
		glGetIntegerv(GL_UNPACK_ALIGNMENT, (GLint *)&alignment);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, (GLuint *)&mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
		glTexImage2D(GL_TEXTURE_2D, 0, mInternalPixelFormat, mWidth, mHeight, 0, mPixelFormat, GL_UNSIGNED_BYTE, (GLvoid*)_data);
		glBindTexture(GL_TEXTURE_2D, 0);

#ifdef PixelBufferObjectSupported
		if (!_data && OpenGLESRenderManager::getInstance().isPixelBufferObjectSupported()) {
            glGenBuffers(1, (GLuint *)&mPboID);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPboID);
			glBufferData(GL_PIXEL_UNPACK_BUFFER, mDataSize, 0, mUsage);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		}
#endif
	}

	void MyTexture::destroy() {
		if (mRenderTarget != nullptr) {
			delete mRenderTarget;
			mRenderTarget = nullptr;
		}

		if (mTextureID != 0) {
			glDeleteTextures(1, (GLuint *)&mTextureID);
			mTextureID = 0;
		}
		if (mPboID != 0) {
            glDeleteBuffers(1, (GLuint *)&mPboID);
			mPboID = 0;
		}

		mWidth = 0;
		mHeight = 0;
		mLock = false;
		mPixelFormat = 0;
		mDataSize = 0;
		mUsage = 0;
		mBuffer = 0;
		mInternalPixelFormat = 0;
		mAccess = 0;
		mNumElemBytes = 0;
		mOriginalFormat = PixelFormat::Unknow;
		mOriginalUsage = TextureUsage::Default;
	}

	int MyTexture::getWidth() {
		return mWidth;
	}
	
	int MyTexture::getHeight() {
		return mHeight;
	}
	
	void* MyTexture::lock(TextureUsage _access) {
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		if (!MyRenderManager::getInstance().isPixelBufferObjectSupported()) {
			mBuffer = new unsigned char[mDataSize];
		} else {
#ifdef PixelBufferObjectSupported
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPboID);
            glBufferData(GL_PIXEL_UNPACK_BUFFER, mDataSize, 0, mUsage);

            mBuffer = (GLubyte*)glMapBufferOES(GL_PIXEL_UNPACK_BUFFER_ARB, mAccess);
			if (!mBuffer) {
                glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
#endif
		}

		mLock = true;
		return mBuffer;
	}

	void MyTexture::unlock() {
		if (!mLock && mBuffer) {
			delete (unsigned char*)mBuffer;
			mBuffer = 0;

			glBindTexture(GL_TEXTURE_2D, 0);
			return;
		}

		if (!MyRenderManager::getInstance().isPixelBufferObjectSupported()) {
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, mPixelFormat, GL_UNSIGNED_BYTE, mBuffer);
			delete (unsigned char*)mBuffer;
		} else {
#ifdef PixelBufferObjectSupported
            glUnmapBufferOES(GL_PIXEL_UNPACK_BUFFER_ARB);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, mPixelFormat, GL_UNSIGNED_BYTE, 0);

            glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
#endif
		}
		
		glBindTexture(GL_TEXTURE_2D, 0);
		mBuffer = 0;
		mLock = false;
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

	void MyTexture::loadFromFile(const std::string& _filename) {
		destroy();

        XE::CImage image;
		if (image.Load(_filename.c_str())) {
            PixelFormat format = PixelFormat::R8G8B8A8;
			int width = image.GetWidth();
			int height = image.GetHeight();
			void* data = image.GetBits();
			if (data) {
				createManual(width, height, TextureUsage::Static | TextureUsage::Write, format, data);
				delete (unsigned char*)data;
			}
		}
	}

	void MyTexture::saveToFile(const std::string& _filename) {

	}

	IRenderTarget* MyTexture::getRenderTarget() {
		if (mRenderTarget == nullptr) {
			mRenderTarget = new MyRTTexture(mTextureID);
		}

		return mRenderTarget;
	}

	unsigned int MyTexture::getTextureID() const {
		return mTextureID;
	}

} // namespace MyGUI
