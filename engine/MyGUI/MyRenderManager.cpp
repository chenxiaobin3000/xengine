#include "stdafx.h"
#include "MyRenderManager.h"
#include "MyTexture.h"
#include "MyVertexBuffer.h"
#include "MyGUI_VertexData.h"
#include "MyGUI_Gui.h"
#include "MyGUI_Timer.h"

const char* vShader = " \n\
\n\
attribute vec3 a_position;                             \n\
attribute vec4 a_color;                                \n\
attribute vec2 a_texCoord;                             \n\
uniform        mat4 u_MVPMatrix;                       \n\
\n\
varying lowp vec4 v_fragmentColor;                     \n\
varying mediump vec2 v_texCoord;                       \n\
\n\
void main()                                            \n\
{                                                      \n\
gl_Position = (vec4(a_position,1));                    \n\
v_fragmentColor = a_color;                             \n\
v_texCoord = a_texCoord;                               \n\
}                                                      \n\
";

const char* fShader = " \n\
precision lowp float;                                  \n\
varying vec4 v_fragmentColor;                          \n\
varying vec2 v_texCoord;                               \n\
uniform sampler2D u_texture;                           \n\
void main(void) {                                      \n\
    gl_FragColor = texture2D(u_texture, v_texCoord);   \n\
}                                                      \n\
";

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
        mProgram = BuildProgram(vShader, fShader);

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

    GLuint MyRenderManager::BuildShader(const char* source, GLenum shaderType) const {
        GLuint shaderHandle = glCreateShader(shaderType);
        glShaderSource(shaderHandle, 1, &source, 0);
        glCompileShader(shaderHandle);
        
        GLint compileSuccess;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
        
        if (compileSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        }
        
        return shaderHandle;
    }
    
    GLuint MyRenderManager::BuildProgram(const char* vertexShaderSource, const char* fragmentShaderSource) const {
        GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
        
        GLuint programHandle = glCreateProgram();
        glAttachShader(programHandle, vertexShader);
        glAttachShader(programHandle, fragmentShader);
        glLinkProgram(programHandle);
        
        GLint linkSuccess;
        glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        }
        
        return programHandle;
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
        
        GLuint positionSlot = glGetAttribLocation(mProgram, "a_position");
        GLuint colorSlot = glGetAttribLocation(mProgram, "a_color");
        GLuint texSlot = glGetAttribLocation(mProgram, "a_texCoord");
        GLuint textureUniform = glGetUniformLocation(mProgram, "u_texture");
        
        glEnableVertexAttribArray(positionSlot);
        glEnableVertexAttribArray(colorSlot);
        glEnableVertexAttribArray(texSlot);
        
        glUseProgram(mProgram);
        
#define kQuadSize sizeof(Vertex)
        
        size_t offset = 0;
        int diff = offsetof(Vertex, x);
        glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
        
        diff = offsetof(Vertex, colour);
        glVertexAttribPointer(colorSlot, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*) (offset + diff));
        
        diff = offsetof(Vertex, u);
        glVertexAttribPointer(texSlot, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
        
        glUniform1i(textureUniform, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, _count);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
	}

	void MyRenderManager::begin() {
        glClearColor(0.8, 0.8, 0.8, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	}

	void MyRenderManager::end() {
		
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
		MyTexture* texture = new MyTexture(_name);
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
