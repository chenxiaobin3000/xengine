/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEPASS_H_
#define _XEPASS_H_

#include "XeCgProgram.h"
#include "XeTexture.h"
#include "XeMatrix.h"
#include "XeColor.h"

namespace XE {

enum EAlphaBlend {
    E_Zero,
    E_One,
    E_SrcColor,
    E_InvSrcColor,
    E_SrcAlpha,
    E_InvSrcAlpha,
    E_DstColor,
    E_InvDstColor,
    E_DstAlpha,
    E_InvDstAlpha,
    E_BlendNum
};

class CPass
{
public:
	CPass();
	virtual ~CPass();

    bool Init(CTexture* pTexture, CColorF& Diffuse, CColorF& Ambient, CColorF& Specular, CColorF& Emissive, CCgProgram* pCgProgram, bool bAlpha=false, EAlphaBlend eSrcBlend=E_One, EAlphaBlend eDstBlend=E_Zero);
    
    void Bind(IRenderEnv* pEnv);
    
    void UnBind();
    
    void SetTarget(IRenderTarget* pTarget);
    
	CCgProgram* GetCgProgram();

	CTexture* GetTexture();
	
	CColorF& GetMaterialDiffuse();
	
	CColorF& GetMaterialAmbient();
	
	CColorF& GetMaterialSpecular();
	
	CColorF& GetMaterialEmissive();

private:
	CCgProgram*					m_pCgProgram;
    
    CTexture*					m_pTexture;				// 纹理
    CTexture*					m_pDepthTexture;		// 深度纹理
    
	CColorF						m_MaterialDiffuse;
	CColorF						m_MaterialAmbient;
	CColorF						m_MaterialSpecular;
	CColorF						m_MaterialEmissive;

   	bool						m_bAlpha;				// 是否透明
	EAlphaBlend					m_eSrcBlend;			// 源参数
	EAlphaBlend					m_eDstBlend;			// 目标参数
};

}

#endif //_XEPASS_H_
