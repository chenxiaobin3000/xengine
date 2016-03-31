#include "stdafx.h"
#include "XePass.h"

namespace XE {

CPass::CPass() : m_pCgProgram(NULL),
				 m_pTexture(NULL),
				 m_pDepthTexture(NULL),
				 m_bAlpha(false),
				 m_eSrcBlend(E_One),
				 m_eDstBlend(E_Zero) {
	
}

CPass::~CPass() {
    XEDELETE(m_pCgProgram);
}

bool CPass::Init(CTexture* pTexture, CColorF& Diffuse, CColorF& Ambient, CColorF& Specular, CColorF& Emissive, CCgProgram* pCgProgram, bool bAlpha, EAlphaBlend eSrcBlend, EAlphaBlend eDstBlend) {
    if (pTexture) {
        m_pTexture = pTexture;
	}
	m_MaterialDiffuse	= Diffuse;
	m_MaterialAmbient	= Ambient;
	m_MaterialSpecular	= Specular;
	m_MaterialEmissive	= Emissive;
    m_pCgProgram        = pCgProgram;
	m_bAlpha			= bAlpha;
	m_eSrcBlend			= eSrcBlend;
	m_eDstBlend			= eDstBlend;
    return true;
}

void CPass::Bind(IRenderEnv* pEnv) {
    if (m_pCgProgram) {
        m_pCgProgram->SetPass(this);
        m_pCgProgram->Bind(pEnv);
    }
}

void CPass::UnBind() {
    if (m_pCgProgram) {
        m_pCgProgram->UnBind();
    }
}

void CPass::SetTarget(IRenderTarget* pTarget) {
    if (m_pCgProgram) {
        m_pCgProgram->SetTarget(pTarget);
    }
}

CCgProgram* CPass::GetCgProgram() {
	return m_pCgProgram;
}

CTexture* CPass::GetTexture() {
    return m_pTexture;
}

CColorF& CPass::GetMaterialDiffuse() {
	return m_MaterialDiffuse;
}

CColorF& CPass::GetMaterialAmbient() {
	return m_MaterialAmbient;
}

CColorF& CPass::GetMaterialSpecular() {
	return m_MaterialSpecular;
}

CColorF& CPass::GetMaterialEmissive() {
	return m_MaterialEmissive;
}

}
