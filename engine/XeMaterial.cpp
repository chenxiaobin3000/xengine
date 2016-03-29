#include "stdafx.h"
#include "XeMaterial.h"

namespace XE {

CMaterial::CMaterial() : m_pTechnique(NULL) {

}

CMaterial::~CMaterial() {
	XEDELETE(m_pTechnique);
}

void CMaterial::Bind(IRenderEnv* pEnv) {
	if (m_pTechnique) {
		m_pTechnique->Bind(pEnv);
	}
}

void CMaterial::UnBind() {
	if (m_pTechnique) {
		m_pTechnique->UnBind();
	}
}

void CMaterial::SetTarget(IRenderTarget* pTarget) {
    if (m_pTechnique) {
        m_pTechnique->SetTarget(pTarget);
    }
}

void CMaterial::SetTechnique(CTechnique* pTechnique) {
    m_pTechnique = pTechnique;
}

CTechnique* CMaterial::GetTechnique() {
    return m_pTechnique;
}

}
