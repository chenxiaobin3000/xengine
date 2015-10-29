/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XERECTANGLE_H_
#define _XERECTANGLE_H_

#include "XePoint.h"
#include "XeTriangle.h"

namespace XE {

class CRect
{
public:
	CRect();

	CRect(float x1, float y1, float x2, float y2);

	virtual ~CRect();

	void Set(float x1, float y1, float x2, float y2);

	float GetWidth();

	float GetHeight();

	bool Contain(CPoint& p, bool bInSize);

	bool Contain(CTriangle& Tri, bool bInSize);

public:
	CPoint						m_p1;
	CPoint						m_p2;
};

}

#endif //_XERECTANGLE_H_
