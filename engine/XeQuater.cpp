#include "stdafx.h"
#include "XeQuater.h"
#include "XeMathDef.h"
#include "XeQuater.h"

namespace XE {

CQuater::CQuater() {
	Identity();
}

CQuater::CQuater(const CQuater& o) {
	x = o.x;  y = o.y;  z = o.z;  w = o.w;
}

CQuater::CQuater(float x, float y, float z, float w) {
	Set(x, y, z, w);
}

CQuater::~CQuater() {

}

bool CQuater::operator==(const CQuater& q) {
	return (IsFloatEqual(x,q.x) && IsFloatEqual(y,q.y) && IsFloatEqual(z,q.z) && IsFloatEqual(w,q.w));
}

bool CQuater::operator!=(const CQuater& q) {
	return (!IsFloatEqual(x,q.x) || !IsFloatEqual(y,q.y) || !IsFloatEqual(z,q.z) || !IsFloatEqual(w,q.w));
}

void CQuater::Set(float ix, float iy, float iz, float iw) {
	x = ix;	y = iy;	z = iz;	w = iw;
}

void CQuater::Identity() {
	x = 0;	y = 0;	z = 0;	w = 1;
}

void CQuater::Inverse() {
	float fNorm = w*w + x*x + y*y + z*z;
	if (fNorm > 0.0) {
		float fInvNorm = (float)(1.0/fNorm);
		x = -x*fInvNorm;
		y = -y*fInvNorm;
		z = -z*fInvNorm;
		w = w*fInvNorm;
	} else {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
}

void CQuater::Normalise() {
	MultNum((float)(1.0 / sqrt(w*w + x*x + y*y + z*z)));
}

void CQuater::FromAngleAxis(float fAngle, const CVertex& v) {
	FromAngleAxis(fAngle, v.x, v.y, v.z);
}

void CQuater::FromAngleAxis(float fAngle, float fAxisX, float fAxisY, float fAxisZ) {
	float fSin = (float)sin(0.5 * fAngle);
	w = (float)cos(0.5 * fAngle);
	x = fSin * fAxisX;
	y = fSin * fAxisY;
	z = fSin * fAxisZ;
}

void CQuater::MultNum(float n) {
	x *= n;  y *= n;  z *= n;  w *= n;
}

void CQuater::Add(CQuater& q) {
	x += q.x;  y += q.y;  z += q.z;  w += q.w;
}

void CQuater::Mult(CQuater& q) {
	float tmp[4];
	tmp[0] = w*q.x + x*q.w + y*q.z - z*q.y;
	tmp[1] = w*q.y - x*q.z + y*q.w + z*q.x;
	tmp[2] = w*q.z + x*q.y - y*q.x + z*q.w;
	tmp[3] = w*q.w - x*q.x - y*q.y - z*q.z;
	x = tmp[0];
	y = tmp[1];
	z = tmp[2];
	w = tmp[3];
}

void CQuater::VertMult(CVertex& v) {
	CVertex uv(x, y, z);
	CVertex uuv(x, y, z);
	uv.CrossMult(v);
	uuv.CrossMult(uv);
	uv.MultNum(2.0f * w);
	uuv.MultNum(2.0f);
	v += uv;
	v += uuv;
}

void CQuater::Slerp(CQuater& axis, float t) {
	CQuater tmp;
	float fCos = w*axis.w + x*axis.x + y*axis.y + z*axis.z;

	if (fCos < (float)0.0) {
		fCos = -fCos;
		tmp.Set(-axis.x, -axis.y, -axis.z, -axis.w);
	} else {
		tmp.Set(axis.x, axis.y, axis.z, axis.w);
	}

	if (fabs(fCos) < 1.0) {
		float fAngle = (float)acos(fCos);
		float fSin = (float)sin(fAngle);
		float fScale0 = (float)(sin((1.0 - t)*fAngle) / fSin);
		float fScale1 = (float)(sin(t*fAngle) / fSin);
		MultNum(fScale0);
		tmp.MultNum(fScale1);
		Add(tmp);
	} else {
		MultNum((float)(1.0-t));
		tmp.MultNum(t);
		Add(tmp);
		Normalise();
	}
}

}
