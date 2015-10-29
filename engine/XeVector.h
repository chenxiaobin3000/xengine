/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XEVECTOR_H_
#define _XEVECTOR_H_

#include "XeVertex.h"

namespace XE {

class CVector
{
public:
	CVector();

	CVector(const CVector& o);

	CVector(float x, float y, float z, float w);

	virtual ~CVector();

	bool operator==(const CVector& v);

	bool operator!=(const CVector& v);

	void Set(float ix, float iy, float iz, float iw);

	void Identity();

public:
	float						x;
	float						y;
	float						z;
	float						w;
};

}

#endif //_XEVECTOR_H_
