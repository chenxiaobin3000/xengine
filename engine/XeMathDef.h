/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEMATHDEF_H_
#define _XEMATHDEF_H_

namespace XE {

const float PI				= 3.14159f;
const float PI_2			= 1.5708f;
const float MAX_FLOAT		= 100000.0f;

inline bool IsFloatEqual(float f1, float f2) {
	const float fMin = 0.0001f;
	return (fabs(f1-f2) < fMin) ? true : false;
}

inline float ReciprocalSqrt(float x) {
	int i;
	float y;
	float r;

	y = (float)(x * 0.5);
	i = *(int*)(&x);
	i = 0x5f3759df - (i >> 1);
	r = *(float*)(&i);
	r = (float)(r * (1.5 - r * r * y));
	return r;
}

}

#endif //_XEMATHDEF_H_
