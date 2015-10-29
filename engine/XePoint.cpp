#include "stdafx.h"
#include "XePoint.h"
#include "XeMathDef.h"
#include "XeTriangle.h"
#include "XeRectangle.h"

namespace XE {

CPoint::CPoint() {
	Identity();
}

CPoint::CPoint(const CPoint& o) {
	x = o.x;  y = o.y;
}

CPoint::CPoint(float x, float y) {
	Set(x, y);
}

CPoint::~CPoint() {

}

bool CPoint::operator==(const CPoint& p) {
	return (IsFloatEqual(x,p.x) && IsFloatEqual(y,p.y));
}

bool CPoint::operator!=(const CPoint& p) {
	return (!IsFloatEqual(x,p.x) || !IsFloatEqual(y,p.y));
}

void CPoint::Set(float ix, float iy) {
	x = ix;  y = iy;
}

void CPoint::Identity() {
	x = 0;  y = 0;
}

void CPoint::Normalise() {
	float l = (float)sqrt(x*x + y*y);
	if (IsFloatEqual(l, 0)) {
		x = 0;
		y = 0;
	} else {
		x /= l;
		y /= l;
	}
}

void CPoint::MultNum(float n) {
	x *= n;  y *= n;
}

void CPoint::DivNum(float n) {
	x /= n;  y /= n;
}

float CPoint::DotMult(CPoint& p) {
	return x*p.x + y*p.y;
}

// 射线法（x轴正方向）
bool CPoint::IsInPoly(CPoint* poly, int num, bool bInSize) {
	int i, j;
	int cnt = 0;
	for (i=0; i<num; ++i) {
		j = (i==num-1) ? 0 : i+1;
		// 是否交于边
		if (IsFloatEqual((x-poly[i].x)*(poly[j].y-poly[i].y), (y-poly[i].y)*(poly[j].x-poly[i].x))) {
			return bInSize;
		}
		// 边平行x轴
		if (!IsFloatEqual(poly[i].y, poly[j].y)) {
			// 上方
			if (y > poly[i].y && y > poly[j].y) {
				continue;
			}
			// 下方（上闭下开）
			if (y <= poly[i].y && y <= poly[j].y) {
				continue;
			}
			// 右方
			if (x > poly[i].x && x > poly[j].x) {
				continue;
			}
			if (x < (poly[i].x + (poly[j].x-poly[i].x)*(y-poly[i].y)/(poly[j].y-poly[i].y))) {
				++cnt;
			}
		}
	}
	return (cnt%2==1) ? true : false;
}

}
