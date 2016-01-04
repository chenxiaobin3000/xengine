#include "stdafx.h"
#include "XeVector.h"
#include "XeMath.h"

namespace XE {

CVector::CVector() {
	Identity();
}

CVector::CVector(const CVector& o) {
	x = o.x;  y = o.y;  z = o.z;  w = o.w;
}

CVector::CVector(float x, float y, float z, float w) {
	Set(x, y, z, w);
}

CVector::~CVector() {

}

bool CVector::operator==(const CVector& v) {
	return (IsFloatEqual(x,v.x) && IsFloatEqual(y,v.y) 
		&& IsFloatEqual(z,v.z) && IsFloatEqual(w,v.w));
}

bool CVector::operator!=(const CVector& v) {
	return (!IsFloatEqual(x,v.x) || !IsFloatEqual(y,v.y) 
		|| !IsFloatEqual(z,v.z) || !IsFloatEqual(w,v.w));
}

void CVector::Set(float ix, float iy, float iz, float iw) {
	x = ix;  y = iy;  z = iz;  w = iw;
}

void CVector::Identity() {
	x = 0;	y = 0;	z = 0;	w = 0;
}

}
