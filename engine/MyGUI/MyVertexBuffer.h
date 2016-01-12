/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-01- 6
 */

#ifndef _MY_VERTEX_BUFFER_H_
#define _MY_VERTEX_BUFFER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyRenderManager.h"

namespace MyGUI {

	class MyVertexBuffer : public IVertexBuffer
	{
	public:
		MyVertexBuffer();
		virtual ~MyVertexBuffer();

		virtual void setVertexCount(size_t _count);
		virtual size_t getVertexCount();

		virtual Vertex* lock();
		virtual void unlock();

	/*internal:*/
		void destroy();
		void create();

		unsigned int getBufferID() const;

	private:
		unsigned int mBufferID;
		size_t mNeedVertexCount;
		size_t mSizeInBytes;
	};

} // namespace MyGUI

#endif // _MY_VERTEX_BUFFER_H_
