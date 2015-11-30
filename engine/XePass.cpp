#include "stdafx.h"
#include "XePass.h"

namespace XE {

CPass::CPass() {
	
}

CPass::~CPass() {
	
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
