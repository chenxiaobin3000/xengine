#include "stdafx.h"
#include "MyRTTexture.h"
#include "MyRenderManager.h"

namespace MyGUI {

	MyRTTexture::MyRTTexture(unsigned int _texture) :
		mTextureID(_texture),
		mWidth(0),
		mHeight(0),
		mFBOID(0),
		mRBOID(0) {
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glBindTexture(GL_TEXTURE_2D, 0);

		mRenderTargetInfo.maximumDepth = 1.0f;
		mRenderTargetInfo.hOffset = 0;
		mRenderTargetInfo.vOffset = 0;
		mRenderTargetInfo.aspectCoef = float(mHeight) / float(mWidth);
		mRenderTargetInfo.pixScaleX = 1.0f / float(mWidth);
		mRenderTargetInfo.pixScaleY = 1.0f / float(mHeight);

        glGenFramebuffers(1, (GLuint *)&mFBOID);
        glBindFramebuffer(GL_FRAMEBUFFER, mFBOID);
        glGenRenderbuffers(1, (GLuint *)&mRBOID);
		glBindRenderbuffer(GL_RENDERBUFFER, mRBOID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, mHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureID, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRBOID);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	MyRTTexture::~MyRTTexture() {
		if (mFBOID != 0) {
            glDeleteFramebuffers(1, (GLuint *)&mFBOID);
			mFBOID = 0;
		}
		if (mRBOID != 0) {
            glDeleteRenderbuffers(1, (GLuint *)&mRBOID);
			mRBOID = 0;
		}
	}

	void MyRTTexture::begin() {
        glBindFramebuffer(GL_FRAMEBUFFER, mFBOID);
		glViewport(0, 0, mWidth, mHeight);

		MyRenderManager::getInstance().begin();
		glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
	}

	void MyRTTexture::end() {
		MyRenderManager::getInstance().end();
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
	}

	void MyRTTexture::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count) {
		MyRenderManager::getInstance().doRender(_buffer, _texture, _count);
	}

    const RenderTargetInfo& MyRTTexture::getInfo() {
        return mRenderTargetInfo;
    }
    
} // namespace MyGUI
