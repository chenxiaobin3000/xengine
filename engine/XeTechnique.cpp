#include "stdafx.h"
#include "XeTechnique.h"

namespace XE {

CTechnique::CTechnique() {

}

CTechnique::~CTechnique() {

}

std::vector<CPass*>& CTechnique::GetPassList() {
	return m_pPassList;
}
	
}
