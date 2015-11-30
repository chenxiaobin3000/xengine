#include "stdafx.h"
#include "XeCamera.h"

namespace XE {
/*
const float	CCamera::s_pn				= -0.99f;
const float	CCamera::s_pf				=  0.99f;
const float CCamera::s_fGridDistance	= 30.0f;
const float CCamera::s_fCameraWidth		= 2.0f;
const float CCamera::s_fCameraHeight	= 2.0f;
const char* CCamera::s_szMatePath		= "mate_bill";

CCamera::CCamera(float vx, float vy, float vz, float width,
				 float height, float zn, float zf) :
	m_ePerspectiveType(ECPT_Perspective),
	m_fScreenWidth(width), 
	m_fScreenHeight(height),
	m_fViewNear(zn),
	m_fViewFar(zf),
	m_bShowGrid(false), 
	m_pCameraGrid(NULL) {
	m_LocalForward.Set(vx, vy, vz);
	m_LocalForward.Normalise();
	m_Forward.Set(vx, vy, vz);

#ifdef SHOW_CAMERA
	m_pBillBoard = NEW_LOG(CBillBoard);
	m_pBillBoard->Init(s_fCameraWidth, s_fCameraHeight, s_szMatePath, EBBT_Spherical);
#else
	m_pBillBoard = NULL;
#endif //SHOW_CAMERA
}

CCamera::~CCamera() {
	if (m_pBillBoard) {
		delete m_pBillBoard;
	}
}

void CCamera::Render(CSceneObject* pCamera, ERenderType eType) {
	if (this == pCamera) {
		if (m_bShowGrid) {
			if (!m_pCameraGrid) {
				CVertex v = GetGridPosition();
				float x1 = v.x;
				float y1 = v.y;
				float z1 = v.z;
				float x2 = CDynamicMesh::AddBaseUnit(v.x);
				float y2 = CDynamicMesh::AddBaseUnit(v.y);
				float z2 = CDynamicMesh::AddBaseUnit(v.z);
				m_LineList.clear();

				// 下层
				v.Set(x1, y1, z1);		m_LineList.PUSH(v);
				v.Set(x2, y1, z1);		m_LineList.PUSH(v);
				v.Set(x1, y1, z1);		m_LineList.PUSH(v);
				v.Set(x1, y2, z1);		m_LineList.PUSH(v);
				v.Set(x2, y1, z1);		m_LineList.PUSH(v);
				v.Set(x2, y2, z1);		m_LineList.PUSH(v);
				v.Set(x1, y2, z1);		m_LineList.PUSH(v);
				v.Set(x2, y2, z1);		m_LineList.PUSH(v);

				// 上层
				v.Set(x1, y1, z2);		m_LineList.PUSH(v);
				v.Set(x2, y1, z2);		m_LineList.PUSH(v);
				v.Set(x1, y1, z2);		m_LineList.PUSH(v);
				v.Set(x1, y2, z2);		m_LineList.PUSH(v);
				v.Set(x2, y1, z2);		m_LineList.PUSH(v);
				v.Set(x2, y2, z2);		m_LineList.PUSH(v);
				v.Set(x1, y2, z2);		m_LineList.PUSH(v);
				v.Set(x2, y2, z2);		m_LineList.PUSH(v);

				// 边柱
				v.Set(x1, y1, z1);		m_LineList.PUSH(v);
				v.Set(x1, y1, z2);		m_LineList.PUSH(v);
				v.Set(x1, y2, z1);		m_LineList.PUSH(v);
				v.Set(x1, y2, z2);		m_LineList.PUSH(v);
				v.Set(x2, y1, z1);		m_LineList.PUSH(v);
				v.Set(x2, y1, z2);		m_LineList.PUSH(v);
				v.Set(x2, y2, z1);		m_LineList.PUSH(v);
				v.Set(x2, y2, z2);		m_LineList.PUSH(v);
			} else {
				CVertex v = GetGridPosition();
				CVertex tmp;
				m_LineList.clear();

				CVertexList& list = m_pCameraGrid->GetLineList(v.x, v.y, v.z);
				auto ite = list.begin();
				auto end = list.end();
				for (; end!=ite; ++ite) {
					tmp.x = ite->x;  tmp.y = ite->y;  tmp.z = ite->z;
					m_LineList.PUSH(tmp);
				}
			}

			CLineBuffer::GetSingleton().DrawLine(m_LineList, COLOR_RED);
		}
	} else {
#ifdef SHOW_CAMERA
		m_pBillBoard->SetPosition(m_Position);
		m_pBillBoard->Render(pCamera, eType);
#endif //SHOW_CAMERA
	}
}

void CCamera::SetCanLook(bool bCanLook) {
	m_bCanLook = bCanLook;
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

CVertex& CCamera::World2Screen(CVertex& WorldVertex) {
	_World2Screen(m_ScreenVertex, WorldVertex, m_fScreenWidth, m_fScreenHeight);
	return m_ScreenVertex;
}

CVertex& CCamera::Screen2World(CVertex& ScreenVertex) {
	_Screen2World(m_WorldVertex, ScreenVertex, m_fScreenWidth, m_fScreenHeight);
	return m_WorldVertex;
}

CVertex& CCamera::GetGridPosition() {
	m_GridVertex = m_LocalForward;
	m_GridVertex.MultNum(s_fGridDistance);
	m_GridVertex += m_Position;
	int x = (int)CDynamicMesh::DivBaseUnit(m_GridVertex.x);
	int y = (int)CDynamicMesh::DivBaseUnit(m_GridVertex.y);
	int z = (int)CDynamicMesh::DivBaseUnit(m_GridVertex.z);
	m_GridVertex.Set(
		CDynamicMesh::MultBaseUnit((float)x), 
		CDynamicMesh::MultBaseUnit((float)y), 
		CDynamicMesh::MultBaseUnit((float)z));
	return m_GridVertex;
}

bool CCamera::IsAttachGrid() {
	return (NULL != m_pCameraGrid);
}

void CCamera::AttachGrid(CCameraGrid* ob) {
	m_pCameraGrid = ob;
}

void CCamera::DetachGrid() {
	m_pCameraGrid = NULL;
}*/

/* 7-----8
 * |\   /|
 * | 3-4 |
 * 5-|-|-6
 *  \| |/
 *   1-2
 */
/*void CCamera::GenerateViewCone(float width, float height) {
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
}*/

}
