/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-12-29
 */

#ifndef _XEGLH_H_
#define _XEGLH_H_

namespace XE {

// 以下函数从 glhlib 库移植
void glhOrtho(float *matrix, float left, float right, float bottom,
			  float top, float znear, float zfar);

void glhFrustum(float* matrix, float left, float right, float bottom,
				 float top, float znear, float zfar);

void glhLookAt(float* matrix, float* eyePosition3D, float* center3D,
			   float* upVector3D);

}

#endif //_XEGLH_H_
