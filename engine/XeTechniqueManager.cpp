#include "stdafx.h"
#include "XeTechniqueManager.h"

namespace XE {

CTechniqueManager::CTechniqueManager() : m_eTechnique(E_TechniqueNormal) {
	
}

CTechniqueManager::~CTechniqueManager() {
	
}

bool CTechniqueManager::Init() {
    return false;
}

void CTechniqueManager::Free() {
	
}

void CTechniqueManager::SetTechnique(ETechniqueType type) {
	m_eTechnique = type;
}

ETechniqueType CTechniqueManager::GetTechnique() {
	return m_eTechnique;
}

}
