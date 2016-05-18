/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEVERTEXBUFFER_H_
#define _XEVERTEXBUFFER_H_

#include "XeIVertexBuffer.h"

namespace XE {

class CVertexBuffer : public IVertexBuffer
{
public:
	CVertexBuffer();
	virtual ~CVertexBuffer();

	virtual void Render();
	
	virtual bool SetVertexCount(int nVertexCount);
	virtual int GetVertexCount();
	virtual bool SetIndexCount(int nIndexCount);
	virtual int GetIndexCount();

	virtual bool Lock(float*& pVertexs, float*& pTexCoords, float*& pNormals, unsigned int*& pIndexs);
	virtual void Unlock();

private:
	int							m_nVertexCount;			// 顶点数
	int							m_nIndexCount;			// 索引数

	GLuint						m_nVBOVertices;			// 顶点id
	float*						m_pVBOVertices;			// 顶点缓冲
	GLuint						m_nVBOTexCoords;		// 纹理id
	float*						m_pVBOTexCoords;		// 纹理缓冲
	GLuint						m_nVBONormals;			// 法线id
	float*						m_pVBONormals;			// 法线缓冲
	GLuint*						m_pIndexList;			// 索引缓冲
};

}

#endif //_XEIVERTEXBUFFER_H_
