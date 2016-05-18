#include "stdafx.h"
#include "XeAction.h"

namespace XE {

CAction::CKeyFrame::CKeyFrame() : m_nTime(0)  {

}

CAction::CAction() : m_nTime(0) {

}

CAction::~CAction() {

}

void CAction::Init(int nTime) {
    m_nTime = nTime;
}

void CAction::Insert(int nID, CAction::CKeyList& List) {
    m_Track.XEINSERT(TrackMapValue(nID, List));
}
    
bool CAction::GetKeyFrame(int nBoneID, int nFrame, CKeyFrame*& pCurrent, CKeyFrame*& pNext) {
	pCurrent = NULL;
	pNext = NULL;

	auto ite = m_Track.find(nBoneID);
	if (m_Track.end() == ite) {
		return false;
	}

	auto ite_l = ite->second.begin();
	auto end_l = ite->second.end();
	for (; end_l!=ite_l; ++ite_l) {
		if ((*ite_l)->m_nTime > nFrame) {
			pNext = *ite_l;
			break;
		} else if ((*ite_l)->m_nTime == nFrame) {
			pCurrent = *ite_l;
			break;
		} else {
			pCurrent = *ite_l;
		}
	}
	return true;
}

int CAction::GetTime() {
	return m_nTime;
}

}
