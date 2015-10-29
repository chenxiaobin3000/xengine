/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XEQUATER_H_
#define _XEQUATER_H_

#include "XeVertex.h"

namespace XE {

class CQuater
{
public:
	CQuater();

	CQuater(const CQuater& o);

	CQuater(float x, float y, float z, float w);

	virtual ~CQuater();

	bool operator==(const CQuater& q);

	bool operator!=(const CQuater& q);

	void Set(float ix, float iy, float iz, float iw);

	void Identity();

	void Inverse();

	void Normalise();

	void FromAngleAxis(float fAngle, const CVertex& v);

	void FromAngleAxis(float fAngle, float fAxisX, float fAxisY, float fAxisZ);

	void MultNum(float n);

	void Add(CQuater& q);

	void Mult(CQuater& q);

	void VertMult(CVertex& v);

	void Slerp(CQuater& axis, float t);

public:
	float						x;
	float						y;
	float						z;
	float						w;
};

}

#endif //_XEQUATER_H_
