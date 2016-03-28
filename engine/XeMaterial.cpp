#include "stdafx.h"
#include "XeMaterial.h"

namespace XE {

CMaterial::CMaterial() {
	ZeroMemory(m_pTechniqueList, sizeof(CTechnique*)*E_TechniqueMax);
}

CMaterial::~CMaterial() {
	for (int i=0; i<E_TechniqueMax; ++i) {
		XEDELETE(m_pTechniqueList[i]);
	}
}

CTechnique* CMaterial::GetTechnique(ETechniqueType type) {
	return m_pTechniqueList[type];
}

}
