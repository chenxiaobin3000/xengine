/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XETRIANGLE_H_
#define _XETRIANGLE_H_

#include "XePoint.h"

namespace XE {

class CTriangle
{
public:
	CTriangle();

	CTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	
	virtual ~CTriangle();

	bool Contain(CPoint& p, bool bInSize);

public:
	CPoint						m_p1;
	CPoint						m_p2;
	CPoint						m_p3;
};

}

#endif //_XETRIANGLE_H_
