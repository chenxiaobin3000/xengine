/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-01- 7
 */

#ifndef _MY_RENDER_MANAGER_H_
#define _MY_RENDER_MANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_RenderFormat.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_RenderManager.h"

namespace MyGUI {

	class MyRenderManager :
		public RenderManager,
		public IRenderTarget
	{
	public:
		MyRenderManager();

		void initialise();
		void shutdown();

		static MyRenderManager& getInstance();
		static MyRenderManager* getInstancePtr();

		/** @see MyRenderManager::getViewSize */
		virtual const IntSize& getViewSize() const;

		/** @see MyRenderManager::getVertexFormat */
		virtual VertexColourType getVertexFormat();

		/** @see MyRenderManager::isFormatSupported */
		virtual bool isFormatSupported(PixelFormat _format, TextureUsage _usage);

		/** @see MyRenderManager::createVertexBuffer */
		virtual IVertexBuffer* createVertexBuffer();
		/** @see MyRenderManager::destroyVertexBuffer */
		virtual void destroyVertexBuffer(IVertexBuffer* _buffer);

		/** @see MyRenderManager::createTexture */
		virtual ITexture* createTexture(const std::string& _name);
		/** @see MyRenderManager::destroyTexture */
		virtual void destroyTexture(ITexture* _texture);
		/** @see MyRenderManager::getTexture */
		virtual ITexture* getTexture(const std::string& _name);


		/** @see IRenderTarget::begin */
		virtual void begin();
		/** @see IRenderTarget::end */
		virtual void end();
		/** @see IRenderTarget::doRender */
		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);
		/** @see IRenderTarget::getInfo */
		virtual const RenderTargetInfo& getInfo();


	/*internal:*/
		void drawOneFrame();
		void setViewSize(int _width, int _height);
		bool isPixelBufferObjectSupported() const;

	private:
		void destroyAllResources();

	private:
		IntSize mViewSize;
		bool mUpdate;
		VertexColourType mVertexFormat;
		RenderTargetInfo mInfo;

		typedef std::map<std::string, ITexture*> MapTexture;
		MapTexture mTextures;
		bool mPboIsSupported;

		bool mIsInitialise;
	};

} // namespace MyGUI

#endif // _MY_RENDER_MANAGER_H_
