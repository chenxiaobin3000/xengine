/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-04-15
 */

#ifndef _XEFACEINDEX_H_
#define _XEFACEINDEX_H_

namespace XE {

typedef unsigned int		FaceIndexType;

// 面索引
class CFaceIndex
{
public:
	CFaceIndex();
	CFaceIndex(FaceIndexType n1, FaceIndexType n2, FaceIndexType n3);
	virtual ~CFaceIndex();

public:
	FaceIndexType		m_n1;
	FaceIndexType		m_n2;
	FaceIndexType		m_n3;
};

}

#endif //_XEFACEINDEX_H_
