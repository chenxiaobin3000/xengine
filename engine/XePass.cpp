#include "stdafx.h"
#include "XePass.h"

namespace XE {

CPass::CPass() : m_pCgProgram(NULL),
				 m_bBindTexture(false),
				 m_pOriginalTexture(NULL),
				 m_pTexture(NULL),
				 m_pDepthTexture(NULL),
				 m_bAlpha(false),
				 m_eSrcBlend(E_One),
				 m_eDstBlend(E_Zero) {
	
}

CPass::~CPass() {
	
}

bool CPass::Init(CTexture* pTexture, bool bBindTexture, CColorF& Diffuse, CColorF& Ambient, CColorF& Specular, CColorF& Emissive, const char* szCgProgram, bool bAlpha, EAlphaBlend eSrcBlend, EAlphaBlend eDstBlend) {
    if (pTexture) {
        m_pTexture = pTexture;
	}
	m_bBindTexture		= bBindTexture;
	m_MaterialDiffuse	= Diffuse;
	m_MaterialAmbient	= Ambient;
	m_MaterialSpecular	= Specular;
	m_MaterialEmissive	= Emissive;
	m_bAlpha			= bAlpha;
	m_eSrcBlend			= eSrcBlend;
	m_eDstBlend			= eDstBlend;
    return true;
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
