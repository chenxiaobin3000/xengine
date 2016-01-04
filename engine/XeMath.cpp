#include "stdafx.h"
#include "XeMath.h"

namespace XE {

bool IsFloatEqual(float f1, float f2) {
	const float fMin = 0.0001f;
	return (fabs(f1-f2) < fMin) ? true : false;
}

float ReciprocalSqrt(float x) {
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
