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

class CRenderScene : public IRenderEnv
{
public:
	CRenderScene();
	virtual ~CRenderScene();

    virtual void Render(CCamera* camera);
    virtual void Draw();
    
    virtual void SetVisible(bool b);
    virtual bool IsVisible();
    virtual void SetVisibleForShadow(bool b);
    virtual bool IsVisibleForShadow();
    
    virtual CMatrix& GetModelViewProj();

	virtual CTexture* GetDepthTexture();
	virtual CMatrix& GetCameraMatrix();
	virtual CMatrix& GetLightMatrix();
	virtual CVertex& GetEyePosition();
	virtual CColorF& GetAmbientColor();
	virtual CColorF& GetLightColor();
	virtual CVertex& GetLightPosition();

private:
	bool						m_bVisible;				// 可视
	bool						m_bVisibleForShadow;	// 是否生成影子

	CMatrix						m_ModelViewProj;		// 世界矩阵(临时)

	CMatrix						m_CameraMatrix;
	CMatrix						m_LightMatrix;
	CVertex						m_EyePosition;
	CColorF						m_AmbientColor;
	CColorF						m_LightColor;
	CVertex						m_LightPosition;
};

}

#endif //_XERENDERSCENE_H_
