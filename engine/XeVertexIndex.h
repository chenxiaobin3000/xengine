/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-18
 */

#ifndef _XEVERTEXINDEX_H_
#define _XEVERTEXINDEX_H_

namespace XE {

typedef unsigned int		VertexIndexType;

// 面索引
class CVertexIndex
{
public:
	CVertexIndex();
	CVertexIndex(VertexIndexType n1, VertexIndexType n2, VertexIndexType n3);
	virtual ~CVertexIndex();

public:
	VertexIndexType		m_n1;
	VertexIndexType		m_n2;
	VertexIndexType		m_n3;
};

}

#endif //_XEVERTEXINDEX_H_
