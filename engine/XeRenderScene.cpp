#include "stdafx.h"
#include "XeRenderScene.h"

namespace XE {

CRenderScene::CRenderScene() :
	m_bVisible(false),
	m_bVisibleForShadow(false) {

}

CRenderScene::~CRenderScene() {

}

void CRenderScene::Render(CCamera* camera) {

}

void CRenderScene::Draw() {

}

void CRenderScene::SetVisible(bool b) {

}

bool CRenderScene::IsVisible() {
    return m_bVisible;
}

void CRenderScene::SetVisibleForShadow(bool b) {

}

bool CRenderScene::IsVisibleForShadow() {
	return m_bVisibleForShadow;
}

CMatrix& CRenderScene::GetModelViewProj() {
	return m_ModelViewProj;
}
    
CTexture* CRenderScene::GetDepthTexture() {
	return NULL;
}

CMatrix& CRenderScene::GetCameraMatrix() {
	return m_CameraMatrix;
}

CMatrix& CRenderScene::GetLightMatrix() {
	return m_LightMatrix;
}

CVertex& CRenderScene::GetEyePosition() {
	return m_EyePosition;
}

CColorF& CRenderScene::GetAmbientColor() {
	return m_AmbientColor;
}

CColorF& CRenderScene::GetLightColor() {
	return m_LightColor;
}

CVertex& CRenderScene::GetLightPosition() {
	return m_LightPosition;
}

}
