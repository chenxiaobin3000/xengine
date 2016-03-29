#include "stdafx.h"
#include "XeTechnique.h"

namespace XE {

CTechnique::CTechnique() : m_pPass(NULL) {

}

CTechnique::~CTechnique() {
    XEDELETE(m_pPass);
}

void CTechnique::Bind(IRenderEnv* pEnv) {
    if (m_pPass) {
        m_pPass->Bind(pEnv);
    }
}

void CTechnique::UnBind() {
    if (m_pPass) {
        m_pPass->UnBind();
    }
}

void CTechnique::SetTarget(IRenderTarget* pTarget) {
    if (m_pPass) {
        m_pPass->SetTarget(pTarget);
    }
}

void CTechnique::SetPass(CPass* pPass) {
    m_pPass = pPass;
}

CPass* CTechnique::GetPass() {
    return m_pPass;
}

}
