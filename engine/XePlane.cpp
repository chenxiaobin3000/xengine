#include "stdafx.h"
#include "XePlane.h"
#include "XeMathDef.h"

namespace XE {

CPlane::CPlane() {
	Identity();
}

CPlane::CPlane(const CPlane& o) {
	x = o.x;  y = o.y;  z = o.z;  w = o.w;
}

CPlane::CPlane(float x, float y, float z, float w) {
	Set(x, y, z, w);
}

CPlane::~CPlane() {

}

bool CPlane::operator==(const CPlane& p) {
	return (IsFloatEqual(x,p.x) && IsFloatEqual(y,p.y) 
		&& IsFloatEqual(z,p.z) && IsFloatEqual(w,p.w));
}

bool CPlane::operator!=(const CPlane& p) {
	return (!IsFloatEqual(x,p.x) || !IsFloatEqual(y,p.y) 
		|| !IsFloatEqual(z,p.z) || !IsFloatEqual(w,p.w));
}

void CPlane::Set(float ix, float iy, float iz, float iw) {
	x = ix;	y = iy;	z = iz;	w = iw;
}

void CPlane::Identity() {
	x = 0;	y = 0;	z = 0;	w = 0;
}

void CPlane::Set(CVertex vct, CVertex pnt) {
	x = vct.x;
	y = vct.y;
	z = vct.z;
	w = -(x*pnt.x + y*pnt.y + z*pnt.z);
}

void CPlane::Set(const CVertex& v1, const CVertex& v2, const CVertex& v3) {
	CVertex tmp1(v2.x-v1.x, v2.y-v1.y, v2.z-v1.z);
	CVertex tmp2(v3.x-v1.x, v3.y-v1.y, v3.z-v1.z);
	tmp1.CrossMult(tmp2);
	tmp1.Normalise();
	x = tmp1.x;
	y = tmp1.y;
	z = tmp1.z;
	w = -(v1.x*tmp1.x + v1.y*tmp1.y + v1.z*tmp1.z);
}

float CPlane::CalcVertex(CVertex v) {
	return x*v.x + y*v.y + z*v.z + w;
}

bool CPlane::IsVertexFocus(CVertex v) {
	return IsFloatEqual(CalcVertex(v), 0);
}

bool CPlane::IsLineFocus(CVertex v, CVertex& focus) {
	float w = -(x*v.x + y*v.y + z*v.z);
	focus.x = -(y*v.y + z*v.z + w)/x;
	focus.y = -(x*v.x + z*v.z + w)/y;
	focus.z = -(x*v.x + y*v.y + w)/z;
	return false;
}

}
