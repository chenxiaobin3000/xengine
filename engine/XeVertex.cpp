#include "stdafx.h"
#include "XeVertex.h"
#include "XeMathDef.h"

namespace XE {

CVertex::CVertex() {
	Identity();
}

CVertex::CVertex(const CVertex& o) {
	x = o.x; y = o.y; z = o.z;
}

CVertex::CVertex(float x, float y, float z) {
	Set(x, y, z);
}

CVertex::~CVertex() {

}

CVertex& CVertex::operator+=(const CVertex& v) {
	x += v.x;  y += v.y;  z += v.z;
	return *this;
}

CVertex& CVertex::operator-=(const CVertex& v) {
	x -= v.x;  y -= v.y;  z -= v.z;
	return *this;
}

bool CVertex::operator==(const CVertex& v) {
	return (IsFloatEqual(x,v.x) && IsFloatEqual(y,v.y) && IsFloatEqual(z,v.z));
}

bool CVertex::operator!=(const CVertex& v) {
	return (!IsFloatEqual(x,v.x) || !IsFloatEqual(y,v.y) || !IsFloatEqual(z,v.z));
}

void CVertex::Set(float ix, float iy, float iz) {
	x = ix;	y = iy;	z = iz;
}

void CVertex::Identity() {
	x = 0;	y = 0;	z = 0;
}

void CVertex::Normalise() {
	float l = Length();
	if (IsFloatEqual(l, 0)) {
		x = 0;
		y = 0;
		z = 0;
	} else {
		x /= l;
		y /= l;
		z /= l;
	}
}

float CVertex::Length() {
	return (float)sqrt(x*x + y*y + z*z);
}

void CVertex::MultNum(float n) {
	x *= n;	y *= n;	z *= n;
}

void CVertex::DivNum(float n) {
	x /= n;	y /= n;	z /= n;
}

float CVertex::DotMult(const CVertex& v) {
	return x*v.x + y*v.y + z*v.z;
}

void CVertex::CrossMult(const CVertex& v) {
	CVertex tmp(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
}

void CVertex::CalcNormal(const CVertex& v1, const CVertex& v2, const CVertex& v3) {
	x = v2.x - v1.x;
	y = v2.y - v1.y;
	z = v2.z - v1.z;
	CrossMult(CVertex(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z));
	Normalise();
}

}
