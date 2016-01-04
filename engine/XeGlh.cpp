#include "stdafx.h"
#include "XeGlh.h"
#include "XeMath.h"

namespace XE {

void NormalizeVector(float* pvector) {
	float normalizingConstant = 1.0f / sqrtf(pvector[0] * pvector[0] + 
		pvector[1] * pvector[1] + pvector[2] * pvector[2]);
	pvector[0] *= normalizingConstant;
	pvector[1] *= normalizingConstant;
	pvector[2] *= normalizingConstant;
}

void ComputeNormalOfPlane(float* normal, const float* pvector1, const float* pvector2) {
	normal[0] = (pvector1[1] * pvector2[2]) - (pvector1[2] * pvector2[1]);
	normal[1] = (pvector1[2] * pvector2[0]) - (pvector1[0] * pvector2[2]);
	normal[2] = (pvector1[0] * pvector2[1]) - (pvector1[1] * pvector2[0]);
}

void glhTranslate(float* matrix, float x, float y, float z) {
	matrix[12] = matrix[0] * x + matrix[4] * y + matrix[8] * z + matrix[12];
	matrix[13] = matrix[1] * x + matrix[5] * y + matrix[9] * z + matrix[13];
	matrix[14] = matrix[2] * x + matrix[6] * y + matrix[10] * z + matrix[14];
	matrix[15] = matrix[3] * x + matrix[7] * y + matrix[11] * z + matrix[15];
}

void MultiplyMatrices4by4(float* result, float* matrix1, float* matrix2) {
	result[0] = matrix1[0] * matrix2[0] + matrix1[4] * matrix2[1] + 
		matrix1[8] * matrix2[2] + matrix1[12] * matrix2[3];
	result[4] = matrix1[0] * matrix2[4] + matrix1[4] * matrix2[5] + 
		matrix1[8] * matrix2[6] + matrix1[12] * matrix2[7];
	result[8] = matrix1[0] * matrix2[8] + matrix1[4] * matrix2[9] + 
		matrix1[8] * matrix2[10] + matrix1[12] * matrix2[11];
	result[12] = matrix1[0] * matrix2[12] + matrix1[4] * matrix2[13] + 
		matrix1[8] * matrix2[14] + matrix1[12] * matrix2[15];

	result[1] = matrix1[1] * matrix2[0] + matrix1[5] * matrix2[1] + 
		matrix1[9] * matrix2[2] + matrix1[13] * matrix2[3];
	result[5] = matrix1[1] * matrix2[4] + matrix1[5] * matrix2[5] + 
		matrix1[9] * matrix2[6] + matrix1[13] * matrix2[7];
	result[9] = matrix1[1] * matrix2[8] + matrix1[5] * matrix2[9] + 
		matrix1[9] * matrix2[10] + matrix1[13] * matrix2[11];
	result[13] = matrix1[1] * matrix2[12] + matrix1[5] * matrix2[13] + 
		matrix1[9] * matrix2[14] + matrix1[13] * matrix2[15];

	result[2] = matrix1[2] * matrix2[0] + matrix1[6] * matrix2[1] + 
		matrix1[10] * matrix2[2] + matrix1[14] * matrix2[3];
	result[6] = matrix1[2] * matrix2[4] + matrix1[6] * matrix2[5] + 
		matrix1[10] * matrix2[6] + matrix1[14] * matrix2[7];
	result[10] = matrix1[2] * matrix2[8] + matrix1[6] * matrix2[9] + 
		matrix1[10] * matrix2[10] + matrix1[14] * matrix2[11];
	result[14] = matrix1[2] * matrix2[12] + matrix1[6] * matrix2[13] + 
		matrix1[10] * matrix2[14] + matrix1[14] * matrix2[15];

	result[3] = matrix1[3] * matrix2[0] + matrix1[7] * matrix2[1] + 
		matrix1[11] * matrix2[2] + matrix1[15] * matrix2[3];
	result[7] = matrix1[3] * matrix2[4] + matrix1[7] * matrix2[5] + 
		matrix1[11] * matrix2[6] + matrix1[15] * matrix2[7];
	result[11] = matrix1[3] * matrix2[8] + matrix1[7] * matrix2[9] + 
		matrix1[11] * matrix2[10] + matrix1[15] * matrix2[11];
	result[15] = matrix1[3] * matrix2[12] + matrix1[7] * matrix2[13] + 
		matrix1[11] * matrix2[14] + matrix1[15] * matrix2[15];
}

void glhOrtho(float *matrix, float left, float right, float bottom, float top, 
	float znear, float zfar) {
	float matrix2[16], temp2, temp3, temp4, resultMatrix[16];
	temp2 = right-left;
	temp3 = top-bottom;
	temp4 = zfar-znear;
	matrix2[0] = 2.0f / temp2;
	matrix2[1] = 0.0;
	matrix2[2] = 0.0;
	matrix2[3] = 0.0;
	matrix2[4] = 0.0;
	matrix2[5] = 2.0f / temp3;
	matrix2[6] = 0.0;
	matrix2[7] = 0.0;
	matrix2[8] = 0.0;
	matrix2[9] = 0.0;
	matrix2[10] = -2.0f / temp4;
	matrix2[11] = 0.0;
	matrix2[12] = (-right-left) / temp2;
	matrix2[13] = (-top-bottom) / temp3;
	matrix2[14] = (-zfar-znear) / temp4;
	matrix2[15] = 1.0;
	MultiplyMatrices4by4(resultMatrix, matrix, matrix2);

	memcpy(matrix, resultMatrix, sizeof(float)*16);
}

void glhFrustum(float* matrix, float left, float right, float bottom, float top,
	float znear, float zfar) {
	float temp, temp2, temp3, temp4;
	temp = 2.0f * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;
	matrix[0] = temp / temp2;
	matrix[1] = 0.0;
	matrix[2] = 0.0;
	matrix[3] = 0.0;
	matrix[4] = 0.0;
	matrix[5] = temp / temp3;
	matrix[6] = 0.0;
	matrix[7] = 0.0;
	matrix[8] = (right + left) / temp2;
	matrix[9] = (top + bottom) / temp3;
	matrix[10] = (-zfar - znear) / temp4;
	matrix[11] = -1.0;
	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = (-temp * zfar) / temp4;
	matrix[15] = 0.0;
}

void glhLookAt(float* matrix, float* eyePosition3D, float* center3D, float* upVector3D) {
	float forward[3], side[3], up[3];
	float matrix2[16], resultMatrix[16];

	forward[0] = center3D[0] - eyePosition3D[0];
	forward[1] = center3D[1] - eyePosition3D[1];
	forward[2] = center3D[2] - eyePosition3D[2];
	NormalizeVector(forward);

	//Side = forward x up
	ComputeNormalOfPlane(side, forward, upVector3D);
	NormalizeVector(side);

	//Recompute up as: up = side x forward
	ComputeNormalOfPlane(up, side, forward);

	matrix2[0] = side[0];
	matrix2[4] = side[1];
	matrix2[8] = side[2];
	matrix2[12] = 0.0;

	matrix2[1] = up[0];
	matrix2[5] = up[1];
	matrix2[9] = up[2];
	matrix2[13] = 0.0;

	matrix2[2] = -forward[0];
	matrix2[6] = -forward[1];
	matrix2[10] = -forward[2];
	matrix2[14] = 0.0;

	matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
	matrix2[15] = 1.0;

	MultiplyMatrices4by4(resultMatrix, matrix, matrix2);
	glhTranslate(resultMatrix, -eyePosition3D[0], -eyePosition3D[1], -eyePosition3D[2]);

	memcpy(matrix, resultMatrix, sizeof(float)*16);
}

}
