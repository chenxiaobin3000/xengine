#include "stdafx.h"
#include "XeBone.h"

namespace XE {

CBone::CBone() : m_nID(0), m_pParent(NULL), m_pNext(NULL), m_pChild(NULL) {

}

CBone::CBone(const CBone& b) : m_nID(b.m_nID), m_pParent(NULL), m_pNext(NULL), m_pChild(NULL) {
	m_Pose		= b.m_Pose;
	m_Init		= b.m_Init;
	m_Derived	= b.m_Derived;
	m_InverseDerived = b.m_InverseDerived;
}

CBone::~CBone() {

}

CBone& CBone::operator=(const CBone& o) {
	m_nID		= o.m_nID;
	m_pParent	= NULL;
	m_pNext		= NULL;
	m_pChild	= NULL;
	m_Pose		= o.m_Pose;
	m_Init		= o.m_Init;
	m_Derived	= o.m_Derived;
	m_InverseDerived = o.m_InverseDerived;
	return *this;
}

void CountSize(CBone* pBone, void* pParam) {
	++(*(int*)pParam);
}

int CBone::GetSize() {
	int n = 0;
	ForEachBoneForward(this, &n, CountSize);
	return n;
}

void BoneReset(CBone* pBone, void* pParam) {
	pBone->m_Pose = pBone->m_Init;
}

void CBone::Reset() {
	ForEachBoneForward(this, NULL, BoneReset);
}

void BoneDerived(CBone* pBone, void* pParam) {
	if (pBone->m_pParent) {
		CQuater q(pBone->m_pParent->m_Derived.rot);
		
		pBone->m_Derived.pos = pBone->m_Pose.pos;
		q.VertMult(pBone->m_Derived.pos);
		pBone->m_Derived.pos += pBone->m_pParent->m_Derived.pos;

		q.Mult(pBone->m_Pose.rot);
		pBone->m_Derived.rot = q;
	} else {
		pBone->m_Derived = pBone->m_Pose;
	}
}

void CBone::Derived() {
	ForEachBoneForward(this, NULL, BoneDerived);
}

void BonePose(CBone* pBone, void* pParam) {
	CVertex& pos = pBone->m_Derived.pos;
	pBone->m_InverseDerived.pos.Set(-pos.x, -pos.y, -pos.z);
	pBone->m_InverseDerived.rot = pBone->m_Derived.rot;
	pBone->m_InverseDerived.rot.Inverse();
}

void CBone::BindPose() {
	ForEachBoneForward(this, NULL, BonePose);
}

void CBone::ForEachBoneForward(CBone* pNode, void* pParam, ForEachBoneCallback pFunc) {
	pFunc(pNode, pParam);
	if (pNode->m_pChild) {
		ForEachBoneForward(pNode->m_pChild, pParam, pFunc);
	}
	if (pNode->m_pNext) {
		ForEachBoneForward(pNode->m_pNext, pParam, pFunc);
	}
}

void CBone::ForEachBoneBack(CBone* pNode, void* pParam, ForEachBoneCallback pFunc) {
	if (pNode->m_pChild) {
		ForEachBoneBack(pNode->m_pChild, pParam, pFunc);
	}
	if (pNode->m_pNext) {
		ForEachBoneBack(pNode->m_pNext, pParam, pFunc);
	}
	pFunc(pNode, pParam);
}

void FreeBone(CBone* pBone, void* pParam) {
	delete pBone;
}

void CBone::FreeList(CBone* pNode) {
	ForEachBoneBack(pNode, NULL, FreeBone);
}

}
