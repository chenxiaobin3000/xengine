#include "stdafx.h"
#include "XeSkinAssign.h"

namespace XE {

CSkinAssign::CSkinPoint::CSkinPoint(int id, float w) : m_nBoneIdx(id), m_fWeight(w) {

}

CSkinAssign::CSkinPoint::~CSkinPoint() {

}

CSkinAssign::CSkinAssign() {

}

CSkinAssign::~CSkinAssign() {

}

void CSkinAssign::Insert(int nVertexIdx, int nBoneIdx, float fWeight) {
	CSkinPoint sa(nBoneIdx, fWeight);
	auto ite = m_Map.find(nVertexIdx);
	if (m_Map.end() == ite) {
		SAList list;
		list.XEPUSH(sa);
		m_Map.XEINSERT(SAMapValue(nVertexIdx, list));
	} else {
		ite->second.XEPUSH(sa);
	}
}

bool CSkinAssign::Empty() {
	return m_Map.empty();
}

}
