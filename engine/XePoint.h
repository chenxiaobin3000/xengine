/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XEPOINT_H_
#define _XEPOINT_H_

namespace XE {

class CTriangle;
class CRect;

class CPoint
{
public:
	CPoint();

	CPoint(const CPoint& o);

	CPoint(float x, float y);

	virtual ~CPoint();

	bool operator==(const CPoint& p);

	bool operator!=(const CPoint& p);

	void Set(float ix, float iy);

	void Identity();

	void Normalise();

	void MultNum(float n);

	void DivNum(float n);

	// 向量叉乘得到垂直向量，二维叉乘没意义
	float DotMult(CPoint& p);

	bool IsInPoly(CPoint* poly, int num, bool bInSize);

public:
	float	x;
	float	y;
};

typedef std::vector<CPoint>							CPointList;

}

#endif //_XEPOINT_H_
