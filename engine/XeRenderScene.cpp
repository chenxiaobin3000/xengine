#include "stdafx.h"
#include "XeRenderScene.h"

namespace XE {

CRenderScene::CRenderScene() {

}

CRenderScene::~CRenderScene() {

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
