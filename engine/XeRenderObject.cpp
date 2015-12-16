#include "stdafx.h"
#include "XeRenderObject.h"

namespace XE {

const CVertex CRenderObject::s_DefaultForward	( 1.0f,  0.0f,  0.0f);
const CVertex CRenderObject::s_DefaultBack		(-1.0f,  0.0f,  0.0f);
const CVertex CRenderObject::s_DefaultLeft		( 0.0f,  0.0f, -1.0f);
const CVertex CRenderObject::s_DefaultRight		( 0.0f,  0.0f,  1.0f);
const CVertex CRenderObject::s_DefaultUp			( 0.0f,  1.0f,  0.0f);
const CVertex CRenderObject::s_DefaultDown		( 0.0f, -1.0f,  0.0f);

CRenderObject::CRenderObject() : m_bVisible(false),
								 m_bVisibleForShadow(false),
								 m_pMaterial(NULL),
								 m_LocalForward(s_DefaultForward),
								 m_Forward(s_DefaultForward),
								 m_LocalUp(s_DefaultUp) {

}

CRenderObject::~CRenderObject() {

}

void CRenderObject::Begin() {

}

void CRenderObject::End() {

}

void CRenderObject::Render(IRenderEnv* pEnv) {

}

void CRenderObject::SetVisible(bool b) {
	m_bVisible = b;
}

bool CRenderObject::IsVisible() {
	return m_bVisible;
}

void CRenderObject::SetVisibleForShadow(bool b) {
	m_bVisibleForShadow = b;
}

bool CRenderObject::IsVisibleForShadow() {
	return m_bVisibleForShadow;
}

CMatrix& CRenderObject::GetModelViewProj() {
	return m_ModelViewProj;
}

void CRenderObject::SetPosition(const CVertex& v) {
	SetPosition(v.x, v.y, v.z);
}

void CRenderObject::SetPosition(float x, float y, float z) {
	m_AABB.Move(x-m_Position.x, y-m_Position.y, z-m_Position.z);
	m_Position.Set(x, y, z);
	m_Forward.x = m_Position.x + m_LocalForward.x;
	m_Forward.y = m_Position.y + m_LocalForward.y;
	m_Forward.z = m_Position.z + m_LocalForward.z;
	m_Matrix.VertToTM(m_Position);

	if (m_pBody) {
		m_pBody->SetPosition(x, y, z);
	}
}	

void CRenderObject::SetRotation(const CQuater& q) {
	m_LocalForward = s_DefaultForward;

	CVertex tmp;
	m_Matrix.TransPart(tmp);
	m_Matrix.QuaterToRM(q);
	m_Matrix.VertMult(m_LocalForward);
	m_Matrix.VertToTM(tmp);
	m_Forward.x = m_Position.x + m_LocalForward.x;
	m_Forward.y = m_Position.y + m_LocalForward.y;
	m_Forward.z = m_Position.z + m_LocalForward.z;
	m_Rotation = q;

	GenerateAABB();
	if (m_pBody) {
		*(m_pBody->GetAABB()) = m_AABB;
	}
}

void CRenderObject::Move(const CVertex& v) {
	Move(v.x, v.y, v.z);
}

void CRenderObject::Move(float x, float y, float z) {
	CVertex forward(m_LocalForward.x, 0, m_LocalForward.z);
	forward.Normalise();
	CVertex left = forward;
	left.CrossMult(s_DefaultUp);
	left.Normalise();
	CMatrix m(forward, s_DefaultUp, left);

	forward.Set(x, y, z);
	m.VertMult(forward);

	// 移动
	m_Position += forward;
	m_Forward  += forward;
	m_Matrix.Move(forward.x, forward.y, forward.z);

	if (m_pBody) {
		m_pBody->SetPosition(m_Position);
	}
}

void CRenderObject::Roll(float fAngle) {
	CQuater q;
	q.FromAngleAxis(fAngle, m_LocalForward);

	// 旋转
	CMatrix m(q);
	m.VertMult(m_LocalUp);
	m_Matrix.CrossMult3(m);
	m_Matrix.RotationPart(m_Rotation);

	GenerateAABB();
	if (m_pBody) {
		*(m_pBody->GetAABB()) = m_AABB;
	}
}

void CRenderObject::Pitch(float fAngle) {
	CQuater q;
	CVertex v(m_LocalForward);
	v.CrossMult(m_LocalUp);
	v.Normalise();
	q.FromAngleAxis(fAngle, v);

	// 旋转
	CMatrix m(q);
	m.VertMult(m_LocalForward);
	m_Forward.x = m_Position.x + m_LocalForward.x;
	m_Forward.y = m_Position.y + m_LocalForward.y;
	m_Forward.z = m_Position.z + m_LocalForward.z;
	m_Matrix.CrossMult3(m);
	m_Matrix.RotationPart(m_Rotation);

	GenerateAABB();
	if (m_pBody) {
		*(m_pBody->GetAABB()) = m_AABB;
	}
}

void CRenderObject::Yaw(float fAngle) {
	CQuater q;
	q.FromAngleAxis(fAngle, m_LocalUp);

	// 旋转
	CMatrix m(q);
	m.VertMult(m_LocalForward);
	m_Forward.x = m_Position.x + m_LocalForward.x;
	m_Forward.y = m_Position.y + m_LocalForward.y;
	m_Forward.z = m_Position.z + m_LocalForward.z;
	m_Matrix.CrossMult3(m);
	m_Matrix.RotationPart(m_Rotation);

	GenerateAABB();
	if (m_pBody) {
		*(m_pBody->GetAABB()) = m_AABB;
	}
}

void CRenderObject::Turn2Face(CVertex& pos, EBillBoardType type) {
	if (IsFloatEqual(pos.x, m_Position.x) 
	&&  IsFloatEqual(pos.z, m_Position.z)) {
		return;
	}

	m_Matrix.Identity();
	m_LocalForward = CSceneObject::s_DefaultForward;

	// 目标点到摄像机的投影向量
	CVertex proj(pos.x-m_Position.x, 
		0, pos.z-m_Position.z);
	proj.Normalise();

	// 旋转轴，上下方向
	CVertex up(m_LocalForward);
	up.CrossMult(proj);
	up.Normalise();

	// 旋转角度 = 前方向与投影向量的夹角
	CQuater q;
	float fCos = m_LocalForward.DotMult(proj);
	if (-1 < fCos && fCos < 1) {
		q.FromAngleAxis(acos(fCos), up);
		m_Matrix.QuaterToRM(q);
	}

	if (EBBT_Spherical == type) {
		// 目标点到摄像机的向量
		CVertex v(pos.x-m_Position.x, 
			pos.y-m_Position.y, 
			pos.z-m_Position.z);
		v.Normalise();

		// 旋转轴，左右方向
		up = proj;
		up.CrossMult(v);
		up.Normalise();

		// 旋转角度 = 目标点到摄像机的向量与对应的投影向量的夹角
		fCos = v.DotMult(proj);
		if (-1 < fCos && fCos < 1) {
			q.FromAngleAxis(acos(fCos), up);
			m_Matrix.MultQuater(q);
		}
	}

	m_Matrix.VertMult(m_LocalForward);
	m_Matrix.VertToTM(m_Position);

	m_Forward.x = m_Position.x + m_LocalForward.x;
	m_Forward.y = m_Position.y + m_LocalForward.y;
	m_Forward.z = m_Position.z + m_LocalForward.z;
	m_Matrix.RotationPart(m_Rotation);
}

void CRenderObject::Turn2Face(float x, float y, float z, EBillBoardType type) {
	CVertex v(x, y, z);
	Turn2Face(v, type);
}

CVertex& CRenderObject::GetLocalForward() {
	return m_LocalForward;
}

CVertex& CRenderObject::GetForward() {
	return m_Forward;
}

CVertex& CRenderObject::GetPosition() {
	return m_Position;
}

CQuater& CRenderObject::GetRotation() {
	return m_Rotation;
}

CAABB& CRenderObject::GetAABB() {
	return m_AABB;
}
	
}
