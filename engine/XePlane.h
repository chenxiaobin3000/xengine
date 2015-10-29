/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XEPLANE_H_
#define _XEPLANE_H_

#include "XeVertex.h"

namespace XE {

class CPlane
{
public:
	CPlane();

	CPlane(const CPlane& o);

	CPlane(float x, float y, float z, float w);

	virtual ~CPlane();

	bool operator==(const CPlane& p);

	bool operator!=(const CPlane& p);

	void Set(float ix, float iy, float iz, float iw);

	void Identity();

	// 设置值，vct平面向量，pnt平面上的点
	void Set(CVertex vct, CVertex pnt);

	// 设置值，三点确定平面
	void Set(const CVertex& v1, const CVertex& v2, const CVertex& v3);

	// 代入点计算
	float CalcVertex(CVertex v);

	// 判断点相交
	bool IsVertexFocus(CVertex v);

	// 判断向量相交
	bool IsLineFocus(CVertex v, CVertex& focus);

private:
	float	x;
	float	y;
	float	z;
	float	w;
};

}

#endif //_XEPLANE_H_
