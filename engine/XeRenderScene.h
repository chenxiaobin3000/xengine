/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-10
 */

#ifndef _XERENDERSCENE_H_
#define _XERENDERSCENE_H_

#include "XeIRenderEnv.h"
#include "XeMatrix.h"
#include "XeVertex.h"
#include "XeColor.h"

// 渲染情景
namespace XE {

class CRenderScene : IRenderEnv
{
public:
	CRenderScene();
	virtual ~CRenderScene();

	virtual CTexture* GetDepthTexture();

	virtual CMatrix& GetCameraMatrix();
	
	virtual CMatrix& GetLightMatrix();

	virtual CVertex& GetEyePosition();

	virtual CColorF& GetAmbientColor();

	virtual CColorF& GetLightColor();

	virtual CVertex& GetLightPosition();

private:
	CMatrix						m_CameraMatrix;
	CMatrix						m_LightMatrix;
	CVertex						m_EyePosition;
	CColorF						m_AmbientColor;
	CColorF						m_LightColor;
	CVertex						m_LightPosition;
};

}

#endif //_XERENDERSCENE_H_
