#include "stdafx.h"
#include "XeCamera.h"
#include "XeGlh.h"
#include "XeMath.h"

namespace XE {

const float	CCamera::s_pn				= -0.99f;
const float	CCamera::s_pf				=  0.99f;

CCamera::CCamera(CVertex& forward, CPoint& screen, float zn, float zf) :
	m_ePerspectiveType(ECPT_Perspective),
	m_fScreenWidth(screen.x), 
	m_fScreenHeight(screen.y),
	m_fViewNear(zn),
	m_fViewFar(zf) {
	m_LocalForward = forward;
	m_LocalForward.Normalise();
	m_Forward = forward;
}
	
CCamera::CCamera(float vx, float vy, float vz, float width,
				 float height, float zn, float zf) :
	m_ePerspectiveType(ECPT_Perspective),
	m_fScreenWidth(width), 
	m_fScreenHeight(height),
	m_fViewNear(zn),
	m_fViewFar(zf) {
	m_LocalForward.Set(vx, vy, vz);
	m_LocalForward.Normalise();
	m_Forward.Set(vx, vy, vz);
}

CCamera::~CCamera() {

}
    
void CCamera::Render(CCamera* camera) {

}

void CCamera::Lookat() {
	GLfloat projection[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	float ymax = m_fViewNear * tanf(45.0f * PI / 360.0f);
	float xmax = ymax * m_fScreenWidth/m_fScreenHeight;
	if (ECPT_Perspective == m_ePerspectiveType) {
		glhFrustum(projection, -xmax, xmax, -ymax, ymax, 
			m_fViewNear, m_fViewFar);
	} else {
		glhOrtho(projection, -xmax, xmax, -ymax, ymax, 
			m_fViewNear, m_fViewFar);
	}

	GLfloat modelview[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	float eye[3] = {m_Position.x, m_Position.y, m_Position.z};
	float center[3] = {m_Forward.x, m_Forward.y, m_Forward.z};
	float v[3] = {CRenderObject::s_DefaultUp.x, CRenderObject::s_DefaultUp.y, CRenderObject::s_DefaultUp.z};
	glhLookAt(modelview, eye, center, v);

	CMatrix tmp;
	TransformMatrix(modelview, &tmp);
	TransformMatrix(projection, &m_RenderMatrix);
	m_RenderMatrix.CrossMult(tmp);
	m_RenderMatrix.Transpose();
}
	
void CCamera::SetPerspectiveType(ECameraPerspectiveType type) {
	m_ePerspectiveType = type;
}

ECameraPerspectiveType CCamera::GetPerspectiveType() {
	return m_ePerspectiveType;
}

float CCamera::GetScreenWidth() {
	return m_fScreenWidth;
}

float CCamera::GetScreenHeight() {
	return m_fScreenHeight;
}

float CCamera::zn() {
	return m_fViewNear;
}

float CCamera::zf() {
	return m_fViewFar;
}

CMatrix& CCamera::GetRenderMatrix() {
	return m_RenderMatrix;
}

CVertex& CCamera::World2Screen(CVertex& WorldVertex) {
	_World2Screen(m_ScreenVertex, WorldVertex, m_fScreenWidth, m_fScreenHeight, m_RenderMatrix);
	return m_ScreenVertex;
}

CVertex& CCamera::Screen2World(CVertex& ScreenVertex) {
	_Screen2World(m_WorldVertex, ScreenVertex, m_fScreenWidth, m_fScreenHeight, m_RenderMatrix);
	return m_WorldVertex;
}

/* 7-----8
 * |\   /|
 * | 3-4 |
 * 5-|-|-6
 *  \| |/
 *   1-2
 */
void CCamera::GenerateViewCone(float width, float height) {
	CVertex v1(0, 0, CCamera::s_pn);
	CVertex v2(width, 0, CCamera::s_pn);
	CVertex v3(0, height, CCamera::s_pn);
	CVertex v4(width, height, CCamera::s_pn);
	CVertex v5(0, 0, CCamera::s_pf);
	CVertex v6(width, 0, CCamera::s_pf);
	CVertex v7(0, height, CCamera::s_pf);
	CVertex v8(width, height, CCamera::s_pf);

	// 近截面
	m_NearPlane.Set(v1, v2, v4);

	// 远截面
	m_FarPlane.Set(v6, v5, v7);

	// 左截面
	m_LeftPlane.Set(v5, v1, v3);

	// 右截面
	m_RightPlane.Set(v2, v6, v8);

	// 上截面
	m_UpPlane.Set(v3, v4, v8);

	// 下截面
	m_DownPlane.Set(v5, v6, v2);
}

void CCamera::TransformMatrix(GLfloat* pFrom, CMatrix* pTo) {
	pTo->Set(
		pFrom[0], pFrom[1], pFrom[2], pFrom[3], 
		pFrom[4], pFrom[5], pFrom[6], pFrom[7], 
		pFrom[8], pFrom[9], pFrom[10], pFrom[11], 
		pFrom[12], pFrom[13], pFrom[14], pFrom[15]);
}

}
