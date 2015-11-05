/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEVERTEXBUFFER_H_
#define _XEVERTEXBUFFER_H_

#include "XeIVertexBuffer.h"

namespace XE {

class CVertexBuffer : IVertexBuffer
{
public:
	CVertexBuffer();
	virtual ~CVertexBuffer();

	virtual void setVertexCount(int value);
	virtual int getVertexCount();

	virtual CVertex* lock();
	virtual void unlock();
};

}

#endif //_XEIVERTEXBUFFER_H_
