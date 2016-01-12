#include "stdafx.h"
#include "MyVertexBuffer.h"
#include "MyGUI_VertexData.h"

namespace MyGUI {

	MyVertexBuffer::MyVertexBuffer() :
        mBufferID(0),
        mNeedVertexCount(0),
		mSizeInBytes(0) {
		
	}

	MyVertexBuffer::~MyVertexBuffer() {
		destroy();
	}

	void MyVertexBuffer::setVertexCount(size_t _count) {
		if (_count != mNeedVertexCount) {
			mNeedVertexCount = _count;
			destroy();
			create();
		}
	}

	size_t MyVertexBuffer::getVertexCount() {
		return mNeedVertexCount;
	}

	Vertex* MyVertexBuffer::lock() {
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, mSizeInBytes, 0, GL_STREAM_DRAW);

		Vertex* pBuffer = reinterpret_cast<Vertex*>(glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return pBuffer;
	}

	void MyVertexBuffer::unlock() {
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glUnmapBufferOES(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void MyVertexBuffer::destroy() {
		if (mBufferID != 0) {
			glDeleteBuffers(1, &mBufferID);
			mBufferID = 0;
		}
	}

	void MyVertexBuffer::create() {
		mSizeInBytes = mNeedVertexCount * sizeof(MyGUI::Vertex);
		void* data = 0;

		glGenBuffers(1, &mBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
		glBufferData(GL_ARRAY_BUFFER, mSizeInBytes, data, GL_STREAM_DRAW);

		int bufferSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
		if (mSizeInBytes != (size_t)bufferSize) {
			destroy();
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	unsigned int MyVertexBuffer::getBufferID() const {
		return mBufferID;
	}
	
} // namespace MyGUI
