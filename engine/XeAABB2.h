/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-12-21
 */

#ifndef _XEAABB2_H_
#define _XEAABB2_H_

#include "XeVertex.h"
#include "XePoint.h"
#include "XeColor.h"

namespace XE {

class CRay;
class CAABB;
class COBB;

class CAABB2
{
public:
	CAABB2();

	CAABB2(CPoint& min, CPoint& max);

	virtual ~CAABB2();

	CAABB2& operator=(const CAABB2& o);

	void Set(CPoint& min, CPoint& max);

	void Set(float x1, float y1, float x2, float y2);

	// 判断相交
	bool Intersect(const CPoint& v);

	// 判断相交(point与vector比较不用y轴)
	bool Intersect(const CVertex& v);

	// 判断相交(point与vector比较不用y轴)
	bool Intersect(const CVertex& v1, const CVertex& v2);

	// 判断相交
	bool Intersect(const CRay& r);

	// 判断相交
	bool Intersect(const CAABB2& pIBB);

	// 判断相交(point与vector比较不用y轴)
	bool Intersect(const CAABB& pIBB);

	// 判断包含
	bool Contain(const CPoint& v);

	// 判断包含(point与vector比较不用y轴)
	bool Contain(const CVertex& v);

	// 判断包含(point与vector比较不用y轴)
	bool Contain(const CVertex& v1, const CVertex& v2);

	// 判断包含
	bool Contain(const CRay& r);

	// 判断包含
	bool Contain(const CAABB2& pIBB);

	// 判断包含(point与vector比较不用y轴)
	bool Contain(const CAABB& pIBB);

	void Render(byte r, byte g, byte b);

	void SetPosition(const CPoint& v);

	void SetPosition(float x, float y);

	void Move(const CPoint& v);

	void Move(float x, float y);
	
	void SetSize(const CPoint& v);

	void SetSize(float x, float y);

public:
	CPoint						m_Min;					// 最小值
	CPoint						m_Max;					// 最大值
};

}

#endif //_XEAABB2_H_
