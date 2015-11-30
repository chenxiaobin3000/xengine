/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEIVERTEXBUFFER_H_
#define _XEIVERTEXBUFFER_H_

#include "XeVertex.h"

namespace XE {

class IVertexBuffer
{
public:
	virtual ~IVertexBuffer() {}

	virtual void Render() = 0;
	
    virtual bool SetCount(int nVertexCount, int nIndexCount) = 0;
	virtual int GetVertexCount() = 0;
	virtual int GetIndexCount() = 0;

	virtual bool Lock(float*& pVertexs, float*& pTexCoords, float*& pNormals, unsigned int*& pIndexs) = 0;
	virtual void Unlock() = 0;
};

}

#endif //_XEIVERTEXBUFFER_H_
