#include "stdafx.h"
#include "XeRenderObject.h"

namespace XE {

CRenderObject::CRenderObject() : m_bVisible(false),
								 m_bVisibleForShadow(false),
								 m_pMaterial(NULL) {

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

}
