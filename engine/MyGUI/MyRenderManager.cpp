#include "stdafx.h"
#include "MyRenderManager.h"
#include "MyTexture.h"
#include "MyVertexBuffer.h"
#include "MyGUI_VertexData.h"
#include "MyGUI_Gui.h"
#include "MyGUI_Timer.h"

namespace MyGUI {

	MyRenderManager& MyRenderManager::getInstance() {
		return *getInstancePtr();
	}

	MyRenderManager* MyRenderManager::getInstancePtr() {
		return static_cast<MyRenderManager*>(RenderManager::getInstancePtr());
	}

	MyRenderManager::MyRenderManager() :
		mUpdate(false),
		mPboIsSupported(false),
		mIsInitialise(false) {
	}

	void MyRenderManager::initialise() {
		mVertexFormat = VertexColourType::ColourABGR;
		mUpdate = false;
		mIsInitialise = true;
	}

	void MyRenderManager::shutdown() {
		destroyAllResources();
		mIsInitialise = false;
	}

	IVertexBuffer* MyRenderManager::createVertexBuffer() {
		return new MyVertexBuffer();
	}

	void MyRenderManager::destroyVertexBuffer(IVertexBuffer* _buffer) {
		delete _buffer;
	}

	void MyRenderManager::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count) {
		MyVertexBuffer* buffer = static_cast<MyVertexBuffer*>(_buffer);
		unsigned int buffer_id = buffer->getBufferID();

		unsigned int texture_id = 0;
		if (_texture) {
			MyTexture* texture = static_cast<MyTexture*>(_texture);
			texture_id = texture->getTextureID();
		}

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		// enable vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// before draw, specify vertex and index arrays with their offsets
		size_t offset = 0;
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offset);
		offset += (sizeof(float) * 3);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offset);
		offset += (4);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offset);

		glDrawArrays(GL_TRIANGLES, 0, _count);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void MyRenderManager::begin() {
		//save current attributes
		//glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
		//glPushAttrib(GL_ALL_ATTRIB_BITS);

		//glPolygonMode(GL_FRONT, GL_FILL);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		//glOrtho(-1, 1, -1, 1, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_FOG);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);

		//glFrontFace(GL_CW);
		//glCullFace(GL_BACK);
		//glEnable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
	}

	void MyRenderManager::end() {
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		//restore former attributes
		//glPopAttrib();
		//glPopClientAttrib();
	}

	const RenderTargetInfo& MyRenderManager::getInfo() {
		return mInfo;
	}

	const IntSize& MyRenderManager::getViewSize() const {
		return mViewSize;
	}

	VertexColourType MyRenderManager::getVertexFormat() {
		return mVertexFormat;
	}

	bool MyRenderManager::isFormatSupported(PixelFormat _format, TextureUsage _usage) {
		return true;
	}

	void MyRenderManager::drawOneFrame() {
		Gui* gui = Gui::getInstancePtr();
		if (gui == nullptr) {
			return;
		}

		static Timer timer;
		static unsigned long last_time = timer.getMilliseconds();
		unsigned long now_time = timer.getMilliseconds();
		unsigned long time = now_time - last_time;

		onFrameEvent((float)((double)(time) / (double)1000));

		last_time = now_time;

		begin();
		onRenderToTarget(this, mUpdate);
		end();

		mUpdate = false;
	}

	void MyRenderManager::setViewSize(int _width, int _height) {
		if (_height == 0) {
			_height = 1;
		}
		if (_width == 0) {
			_width = 1;
		}

		mViewSize.set(_width, _height);

		mInfo.maximumDepth = 1;
		mInfo.hOffset = 0;
		mInfo.vOffset = 0;
		mInfo.aspectCoef = float(mViewSize.height) / float(mViewSize.width);
		mInfo.pixScaleX = 1.0f / float(mViewSize.width);
		mInfo.pixScaleY = 1.0f / float(mViewSize.height);

		onResizeView(mViewSize);
		mUpdate = true;
	}

	bool MyRenderManager::isPixelBufferObjectSupported() const {
		return mPboIsSupported;
	}

	ITexture* MyRenderManager::createTexture(const std::string& _name) {
		OpenGLTexture* texture = new OpenGLTexture(_name, mImageLoader);
		mTextures[_name] = texture;
		return texture;
	}

	void MyRenderManager::destroyTexture(ITexture* _texture) {
		if (_texture == nullptr) {
			return;
		}

		MapTexture::iterator item = mTextures.find(_texture->getName());
		mTextures.erase(item);
		delete _texture;
	}

	ITexture* MyRenderManager::getTexture(const std::string& _name) {
		MapTexture::const_iterator item = mTextures.find(_name);
		if (item == mTextures.end()) {
			return nullptr;
		}
		return item->second;
	}

	void MyRenderManager::destroyAllResources() {
		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item) {
			delete item->second;
		}
		mTextures.clear();
	}

} // namespace MyGUI
