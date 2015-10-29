/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEIVERTEXBUFFER_H_
#define _XEIVERTEXBUFFER_H_

namespace XE {

class IVertexBuffer
{
public:
	virtual ~IVertexBuffer() {}

	virtual void setVertexCount(int value) = 0;
	virtual int getVertexCount() = 0;

	virtual Vertex* lock() = 0;
	virtual void unlock() = 0;
};

}

#endif //_XEIVERTEXBUFFER_H_
