#include "stdafx.h"
#include "XeSkeleton.h"

namespace XE {

CSkeleton::CSkeleton() : m_pRootBone(NULL) {
	int size = m_pRootBone->GetSize();
	m_pMatrixList = XENEW(CMatrix[size]);
}

CSkeleton::~CSkeleton() {
	m_BoneMap.clear();
	CBone::FreeList(m_pRootBone);
	delete[] m_pMatrixList;
}

void CSkeleton::InitPose() {
    m_pRootBone->Derived();
    m_pRootBone->BindPose();
}

bool CSkeleton::SetPose(const char* szAction, int nFrame) {
	auto ite  = m_ActionMap.find(szAction);
	if (m_ActionMap.end() == ite) {
		return false;
	}
	
	SParam param;
	param.pAction = *ite->second;
	param.nFrame = nFrame;

	// 骨骼变换
	m_pRootBone->Reset();
	m_pRootBone->Derived();

	CBone::ForEachBoneForward(m_pRootBone, &param, ApplyTrack);
	m_pRootBone->Derived();
	CBone::ForEachBoneForward(m_pRootBone, this, BoneTransform);

	return true;
}

void CSkeleton::SetRootBone(CBone* pRoot) {
    m_pRootBone = pRoot;
}
    
void CSkeleton::AddBone(const char* szName, CBone* pBone) {
	m_BoneMap.XEINSERT(BoneMapValue(szName, pBone));
}

void CSkeleton::AddAction(const char* szAction, CAction* pAction) {
	m_ActionMap.XEINSERT(ActionMapValue(szAction, pAction));
}

CSkeleton::BoneMap& CSkeleton::GetBoneMap() {
    return m_BoneMap;
}
  
CMatrix* CSkeleton::GetMatrixList() const {
	return m_pMatrixList;
}

int CSkeleton::GetBoneID(const char* szName) const {
	BoneMap::const_iterator ite = m_BoneMap.find(szName);
	if (m_BoneMap.end() != ite) {
		return ite->second->m_nID;
	} else {
		return -1;
	}
}

void CSkeleton::ApplyTrack(CBone* pBone, void* pParam) {
	SParam* p = (SParam*)pParam;
	
	// 索引当前帧信息
	CAction::CKeyFrame* pFrame = NULL;
	CAction::CKeyFrame* pNext = NULL;
	if (!p->pAction.GetKeyFrame(pBone->m_nID, p->nFrame, pFrame, pNext)) {
		return;
	}

	// 插值
	if (!pNext) {
		pBone->m_Pose.pos += pFrame->m_Pos;
		pBone->m_Pose.rot.Mult(pFrame->m_Rot);
	} else {
		CVertex pos_next(pNext->m_Pos);
		float fInc = (float)(p->nFrame-pFrame->m_nTime)/(pNext->m_nTime-pFrame->m_nTime);

		// pos = base + ((next - base) * t)
		pos_next -= pFrame->m_Pos;
		pos_next.MultNum(fInc);
		pBone->m_Pose.pos += pos_next;
		pBone->m_Pose.pos += pFrame->m_Pos;

		CQuater rot_next(pFrame->m_Rot);
		rot_next.Slerp(pNext->m_Rot, fInc);
		pBone->m_Pose.rot.Mult(rot_next);
	}
}

void CSkeleton::BoneTransform(CBone* pBone, void* pParam) {
	CMatrix* pMatrixList = ((CSkeleton*)pParam)->GetMatrixList();

	// 转换矩阵
	pBone->m_Pose.rot = pBone->m_Derived.rot;
	pBone->m_Pose.rot.Mult(pBone->m_InverseDerived.rot);

	CVertex pos(pBone->m_InverseDerived.pos);
	pBone->m_Pose.rot.VertMult(pos);
	pBone->m_Pose.pos = pBone->m_Derived.pos;
	pBone->m_Pose.pos += pos;

	pMatrixList[pBone->m_nID].QuaterToRM(pBone->m_Pose.rot);
	pMatrixList[pBone->m_nID].VertToTM(pBone->m_Pose.pos);
}

}
