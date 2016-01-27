/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-01-20
 */

#ifndef _MY_RTTEXTURE_H_
#define _MY_RTTEXTURE_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_ITexture.h"
#include "MyGUI_RenderFormat.h"
#include "MyGUI_IRenderTarget.h"

namespace MyGUI {

	class MyRTTexture :
		public IRenderTarget
	{
	public:
		MyRTTexture(unsigned int _texture);
		virtual ~MyRTTexture();

		virtual void begin();
		virtual void end();

		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);

        virtual const RenderTargetInfo& getInfo();
        
	private:
		RenderTargetInfo mRenderTargetInfo;
		unsigned int mTextureID;
		int mWidth;
		int mHeight;
		unsigned int mFBOID;
		unsigned int mRBOID;
	};

} // namespace MyGUI

#endif // _MY_RTTEXTURE_H_
