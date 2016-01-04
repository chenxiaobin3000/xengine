#include "stdafx.h"
#include "XeMatrix.h"
#include "XeMath.h"
#include "XeQuater.h"
#include "XeVector.h"

namespace XE {

CMatrix::CMatrix() {
	Identity();
}

CMatrix::CMatrix(float* list) {
	memcpy(m, list, sizeof(float)*E_Num4x4);
}

CMatrix::CMatrix(float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44) {
	Set(_11, _12, _13, _14, _21, _22, _23, _24, 
		_31, _32, _33, _34, _41, _42, _43, _44);
}

CMatrix::CMatrix(const CQuater& q) {
	QuaterToRM(q);
}

CMatrix::CMatrix(const CVertex& x, const CVertex& y, const CVertex& z) {
	Coord(x, y, z);
}

CMatrix::~CMatrix() {

}

void CMatrix::Set(float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44) {
	m[E_11] = _11;	m[E_21] = _21;	m[E_31] = _31;	m[E_41] = _41;
	m[E_12] = _12;	m[E_22] = _22;	m[E_32] = _32;	m[E_42] = _42;
	m[E_13] = _13;	m[E_23] = _23;	m[E_33] = _33;	m[E_43] = _43;
	m[E_14] = _14;	m[E_24] = _24;	m[E_34] = _34;	m[E_44] = _44;
}

void CMatrix::Identity() {
	ZeroMemory(m, sizeof(float)*E_Num4x4);
	m[E_11] = 1;	m[E_22] = 1;	m[E_33] = 1;	m[E_44] = 1;
}

void CMatrix::Inverse() {
	float m00 = m[E_11], m01 = m[E_12], m02 = m[E_13], m03 = m[E_14];
	float m10 = m[E_21], m11 = m[E_22], m12 = m[E_23], m13 = m[E_24];
	float m20 = m[E_31], m21 = m[E_32], m22 = m[E_33], m23 = m[E_34];
	float m30 = m[E_41], m31 = m[E_42], m32 = m[E_43], m33 = m[E_44];
	
	float v0 = m20 * m31 - m21 * m30;
	float v1 = m20 * m32 - m22 * m30;
	float v2 = m20 * m33 - m23 * m30;
	float v3 = m21 * m32 - m22 * m31;
	float v4 = m21 * m33 - m23 * m31;
	float v5 = m22 * m33 - m23 * m32;
	
	float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);
	
	float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);
	
	float d00 = t00 * invDet;
	float d10 = t10 * invDet;
	float d20 = t20 * invDet;
	float d30 = t30 * invDet;
	
	float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;
	
	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;
	
	float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;
	
	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;
	
	float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;
	
	m[E_11] = d00;	m[E_12] = d01;	m[E_13] = d02;	m[E_14] = d03;
	m[E_21] = d10;	m[E_22] = d11;	m[E_23] = d12;	m[E_24] = d13;
	m[E_31] = d20;	m[E_32] = d21;	m[E_33] = d22;	m[E_34] = d23;
	m[E_41] = d30;	m[E_42] = d31;	m[E_43] = d32;	m[E_44] = d33;
}

void CMatrix::Transpose() {
	CMatrix tmp(
		m[0], m[4], m[8], m[12], 
		m[1], m[5], m[9], m[13], 
		m[2], m[6], m[10], m[14], 
		m[3], m[7], m[11], m[15]);
	memcpy(m, tmp.m, sizeof(float)*E_Num4x4);
}

void CMatrix::VertToTM(const CVertex& v) {
	VertToTM(v.x, v.y, v.z);
}

void CMatrix::VertToTM(float x, float y, float z) {
	m[E_14] = x;  m[E_24] = y;  m[E_34] = z;
}

void CMatrix::TransPart(CVertex& v) {
	v.x = m[E_14];  v.y = m[E_24];  v.z = m[E_34];
}

void CMatrix::Move(const CVertex& v) {
	Move(v.x, v.y, v.z);
}

void CMatrix::Move(float x, float y, float z) {
	m[E_14] += x;  m[E_24] += y;  m[E_34] += z;
}

void CMatrix::MultNum(float n) {
	for (int i=0; i<E_Num4x4; ++i) {
		m[i] *= n;
	}
}

void CMatrix::VertMult(CVertex& v) {
	float x, y, z;
	x = m[E_11]*v.x + m[E_12]*v.y + m[E_13]*v.z + m[E_14];
	y = m[E_21]*v.x + m[E_22]*v.y + m[E_23]*v.z + m[E_24];
	z = m[E_31]*v.x + m[E_32]*v.y + m[E_33]*v.z + m[E_34];
	v.x = x;
	v.y = y;
	v.z = z;
}

void CMatrix::VectMult(CVector& v) {
	float x, y, z, w;
	x = m[E_11]*v.x + m[E_12]*v.y + m[E_13]*v.z + m[E_14]*v.w;
	y = m[E_21]*v.x + m[E_22]*v.y + m[E_23]*v.z + m[E_24]*v.w;
	z = m[E_31]*v.x + m[E_32]*v.y + m[E_33]*v.z + m[E_34]*v.w;
	w = m[E_41]*v.x + m[E_42]*v.y + m[E_43]*v.z + m[E_44]*v.w;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
}

void CMatrix::CrossMult(const CMatrix& im) {
#define LEFT_M		im.m
#define RIGHT_M		m
	float _11 = LEFT_M[E_11]*RIGHT_M[E_11] + LEFT_M[E_12]*RIGHT_M[E_21] + LEFT_M[E_13]*RIGHT_M[E_31] + LEFT_M[E_14]*RIGHT_M[E_41];
	float _12 = LEFT_M[E_11]*RIGHT_M[E_12] + LEFT_M[E_12]*RIGHT_M[E_22] + LEFT_M[E_13]*RIGHT_M[E_32] + LEFT_M[E_14]*RIGHT_M[E_42];
	float _13 = LEFT_M[E_11]*RIGHT_M[E_13] + LEFT_M[E_12]*RIGHT_M[E_23] + LEFT_M[E_13]*RIGHT_M[E_33] + LEFT_M[E_14]*RIGHT_M[E_43];
	float _14 = LEFT_M[E_11]*RIGHT_M[E_14] + LEFT_M[E_12]*RIGHT_M[E_24] + LEFT_M[E_13]*RIGHT_M[E_34] + LEFT_M[E_14]*RIGHT_M[E_44];
	
	float _21 = LEFT_M[E_21]*RIGHT_M[E_11] + LEFT_M[E_22]*RIGHT_M[E_21] + LEFT_M[E_23]*RIGHT_M[E_31] + LEFT_M[E_24]*RIGHT_M[E_41];
	float _22 = LEFT_M[E_21]*RIGHT_M[E_12] + LEFT_M[E_22]*RIGHT_M[E_22] + LEFT_M[E_23]*RIGHT_M[E_32] + LEFT_M[E_24]*RIGHT_M[E_42];
	float _23 = LEFT_M[E_21]*RIGHT_M[E_13] + LEFT_M[E_22]*RIGHT_M[E_23] + LEFT_M[E_23]*RIGHT_M[E_33] + LEFT_M[E_24]*RIGHT_M[E_43];
	float _24 = LEFT_M[E_21]*RIGHT_M[E_14] + LEFT_M[E_22]*RIGHT_M[E_24] + LEFT_M[E_23]*RIGHT_M[E_34] + LEFT_M[E_24]*RIGHT_M[E_44];
	
	float _31 = LEFT_M[E_31]*RIGHT_M[E_11] + LEFT_M[E_32]*RIGHT_M[E_21] + LEFT_M[E_33]*RIGHT_M[E_31] + LEFT_M[E_34]*RIGHT_M[E_41];
	float _32 = LEFT_M[E_31]*RIGHT_M[E_12] + LEFT_M[E_32]*RIGHT_M[E_22] + LEFT_M[E_33]*RIGHT_M[E_32] + LEFT_M[E_34]*RIGHT_M[E_42];
	float _33 = LEFT_M[E_31]*RIGHT_M[E_13] + LEFT_M[E_32]*RIGHT_M[E_23] + LEFT_M[E_33]*RIGHT_M[E_33] + LEFT_M[E_34]*RIGHT_M[E_43];
	float _34 = LEFT_M[E_31]*RIGHT_M[E_14] + LEFT_M[E_32]*RIGHT_M[E_24] + LEFT_M[E_33]*RIGHT_M[E_34] + LEFT_M[E_34]*RIGHT_M[E_44];
	
	float _41 = LEFT_M[E_41]*RIGHT_M[E_11] + LEFT_M[E_42]*RIGHT_M[E_21] + LEFT_M[E_43]*RIGHT_M[E_31] + LEFT_M[E_44]*RIGHT_M[E_41];
	float _42 = LEFT_M[E_41]*RIGHT_M[E_12] + LEFT_M[E_42]*RIGHT_M[E_22] + LEFT_M[E_43]*RIGHT_M[E_32] + LEFT_M[E_44]*RIGHT_M[E_42];
	float _43 = LEFT_M[E_41]*RIGHT_M[E_13] + LEFT_M[E_42]*RIGHT_M[E_23] + LEFT_M[E_43]*RIGHT_M[E_33] + LEFT_M[E_44]*RIGHT_M[E_43];
	float _44 = LEFT_M[E_41]*RIGHT_M[E_14] + LEFT_M[E_42]*RIGHT_M[E_24] + LEFT_M[E_43]*RIGHT_M[E_34] + LEFT_M[E_44]*RIGHT_M[E_44];

	m[E_11] = _11;	m[E_21] = _21;	m[E_31] = _31;	m[E_41] = _41;
	m[E_12] = _12;	m[E_22] = _22;	m[E_32] = _32;	m[E_42] = _42;
	m[E_13] = _13;	m[E_23] = _23;	m[E_33] = _33;	m[E_43] = _43;
	m[E_14] = _14;	m[E_24] = _24;	m[E_34] = _34;	m[E_44] = _44;
}

void CMatrix::CrossMult3(const CMatrix& im) {
#define LEFT_M		im.m
#define RIGHT_M		m
	float _11 = LEFT_M[E_11]*RIGHT_M[E_11] + LEFT_M[E_12]*RIGHT_M[E_21] + LEFT_M[E_13]*RIGHT_M[E_31];
	float _12 = LEFT_M[E_11]*RIGHT_M[E_12] + LEFT_M[E_12]*RIGHT_M[E_22] + LEFT_M[E_13]*RIGHT_M[E_32];
	float _13 = LEFT_M[E_11]*RIGHT_M[E_13] + LEFT_M[E_12]*RIGHT_M[E_23] + LEFT_M[E_13]*RIGHT_M[E_33];

	float _21 = LEFT_M[E_21]*RIGHT_M[E_11] + LEFT_M[E_22]*RIGHT_M[E_21] + LEFT_M[E_23]*RIGHT_M[E_31];
	float _22 = LEFT_M[E_21]*RIGHT_M[E_12] + LEFT_M[E_22]*RIGHT_M[E_22] + LEFT_M[E_23]*RIGHT_M[E_32];
	float _23 = LEFT_M[E_21]*RIGHT_M[E_13] + LEFT_M[E_22]*RIGHT_M[E_23] + LEFT_M[E_23]*RIGHT_M[E_33];

	float _31 = LEFT_M[E_31]*RIGHT_M[E_11] + LEFT_M[E_32]*RIGHT_M[E_21] + LEFT_M[E_33]*RIGHT_M[E_31];
	float _32 = LEFT_M[E_31]*RIGHT_M[E_12] + LEFT_M[E_32]*RIGHT_M[E_22] + LEFT_M[E_33]*RIGHT_M[E_32];
	float _33 = LEFT_M[E_31]*RIGHT_M[E_13] + LEFT_M[E_32]*RIGHT_M[E_23] + LEFT_M[E_33]*RIGHT_M[E_33];

	m[E_11] = _11;	m[E_21] = _21;	m[E_31] = _31;
	m[E_12] = _12;	m[E_22] = _22;	m[E_32] = _32;
	m[E_13] = _13;	m[E_23] = _23;	m[E_33] = _33;
}

void CMatrix::MultQuater(const CQuater& q) {
	CrossMult3(CMatrix(q));
}

void CMatrix::QuaterToRM(const CQuater& q) {
	float fQx  = q.x+q.x;
	float fQy  = q.y+q.y;
	float fQz  = q.z+q.z;
	float fQwx = fQx*q.w;
	float fQwy = fQy*q.w;
	float fQwz = fQz*q.w;
	float fQxx = fQx*q.x;
	float fQxy = fQy*q.x;
	float fQxz = fQz*q.x;
	float fQyy = fQy*q.y;
	float fQyz = fQz*q.y;
	float fQzz = fQz*q.z;
	
	m[E_11] = 1.0f-(fQyy+fQzz);
	m[E_12] = fQxy-fQwz;
	m[E_13] = fQxz+fQwy;
	m[E_14] = 0;
	
	m[E_21] = fQxy+fQwz;
	m[E_22] = 1.0f-(fQxx+fQzz);
	m[E_23] = fQyz-fQwx;
	m[E_24] = 0;
	
	m[E_31] = fQxz-fQwy;
	m[E_32] = fQyz+fQwx;
    m[E_33] = 1.0f-(fQxx+fQyy);
	m[E_34] = 0;
	
	m[E_41] = 0;
	m[E_42] = 0;
	m[E_43] = 0;
	m[E_44] = 1;
}

void CMatrix::RotationPart(CQuater& q) {
	float fT = m[E_11] + m[E_22] + m[E_33];
	float fS;

	if (fT > 0.0) {
		fT += 1.0;
		fS = (float)(ReciprocalSqrt(fT) * 0.5);

		q.w = fS * fT;
		q.x = (m[E_32] - m[E_23]) * fS;
		q.y = (m[E_13] - m[E_31]) * fS;
		q.z = (m[E_21] - m[E_12]) * fS;
	} else if (m[E_11] > m[E_22] && m[E_11] > m[E_33]) {
		fT = m[E_11] - m[E_22] - m[E_33] + (float)1.0;
		fS = (float)(ReciprocalSqrt(fT) * 0.5);

		q.w = (m[E_32] - m[E_23]) * fS;
		q.x = fS * fT;
		q.y = (m[E_21] + m[E_12]) * fS;
		q.z = (m[E_13] + m[E_31]) * fS;
	} else if (m[E_22] > m[E_33]) {
		fT = -m[E_11] + m[E_22] - m[E_33] + (float)1.0;
		fS = (float)(ReciprocalSqrt(fT) * 0.5);

		q.w = (m[E_13] - m[E_31]) * fS;
		q.x = (m[E_21] + m[E_12]) * fS;
		q.y = fS * fT;
		q.z = (m[E_32] + m[E_23]) * fS;
	} else {
		fT = -m[E_11] - m[E_22] + m[E_33] + (float)1.0;
		fS = (float)(ReciprocalSqrt(fT) * 0.5);

		q.w = (m[E_21] - m[E_12]) * fS;
		q.x = (m[E_13] + m[E_31]) * fS;
		q.y = (m[E_32] + m[E_23]) * fS;
		q.z = fS * fT;
	}
}

void CMatrix::Coord(const CVertex& x, const CVertex& y, const CVertex& z) {
	m[E_11] = x.x;	m[E_21] = x.y;	m[E_31] = x.z;	m[E_41] = 0;
	m[E_12] = y.x;	m[E_22] = y.y;	m[E_32] = y.z;	m[E_42] = 0;
	m[E_13] = z.x;	m[E_23] = z.y;	m[E_33] = z.z;	m[E_43] = 0;
	m[E_14] = 0;	m[E_24] = 0;	m[E_34] = 0;	m[E_44] = 1;
}

}
