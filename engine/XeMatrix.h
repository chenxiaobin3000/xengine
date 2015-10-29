/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEMATRIX_H_
#define _XEMATRIX_H_

#include "XeVertex.h"

namespace XE {

class CQuater;
class CVector;

class CMatrix
{
public:
	enum EMatrix {
		E_11,	E_12,	E_13,	E_14,
		E_21,	E_22,	E_23,	E_24,
		E_31,	E_32,	E_33,	E_34,
		E_41,	E_42,	E_43,	E_44,
		E_Num4x4
	};

public:
	CMatrix();
	
	CMatrix(float* list);

	CMatrix(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44);
	
	CMatrix(const CQuater& q);

	CMatrix(const CVertex& x, const CVertex& y, const CVertex& z);

	virtual ~CMatrix();

	void Set(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44);

	void Identity();
	
	void Inverse();

	void Transpose();

	void VertToTM(const CVertex& v);

	void VertToTM(float x, float y, float z);

	void TransPart(CVertex& v);

	void Move(const CVertex& v);

	void Move(float x, float y, float z);

	void MultNum(float n);

	// this->mult(v) = this * v
	void VertMult(CVertex& v);

	// this->mult(v) = this * v
	void VectMult(CVector& v);

	// this->cross(m) = m * this
	void CrossMult(const CMatrix& im);

	// this->cross(m) = m * this
	void CrossMult3(const CMatrix& im);
	
	// 以原点为圆心做旋转
	void MultQuater(const CQuater& q);

	void QuaterToRM(const CQuater& q);

	void RotationPart(CQuater& q);

	// 基变换 － 生成坐标系
	void Coord(const CVertex& x, const CVertex& y, const CVertex& z);

public:
	float m[E_Num4x4];
};

}

#endif //_XEMATRIX_H_
