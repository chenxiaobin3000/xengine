#include "stdafx.h"
#include "XeSkeletonLoader.h"
#include "XeBone.h"
#include "XeXFile.h"
#include "XeAction.h"
#include "XeTimer.h"

namespace XE {

CSkeletonLoader::CSkeletonLoader() {
}

CSkeletonLoader::~CSkeletonLoader() {
}

CSkeleton* CSkeletonLoader::Load(const char* szName) {
    return NULL;
}

bool CSkeletonLoader::LoadXml(const char* szPath) {
    byte* buffer = NULL;
	unsigned int size = 0;
	if (!CXFile::ReadText(szPath, buffer, size)) {
		XELOG("load skeleton error: %s", szPath);
		return false;
	}

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse((const char*)buffer);
    if (error != tinyxml2::XML_SUCCESS) {
		XELOG("parse skeleton err: %s\n", szPath);
		return false;
	}

    tinyxml2::XMLElement* root = doc.RootElement();
	if (!root) {
        XELOG("parse skeleton get root error: %s", szPath);
		return false;
	}
	if (0 != strcmp(root->Value(), "skeleton")) {
        XELOG("parse skeleton find skeleton error: %s", szPath);
		return false;
	}

    CSkeleton* pSkeleton = XENEW(CSkeleton);
    if (!pSkeleton) {
        return false;
    }

	if (!LoadSkeleton(root, pSkeleton)) {
        XELOG("parse skeleton load skeleton error: %s", szPath);
        XEDELETE(pSkeleton);
		return false;
	}
    
	return true;
}

bool CSkeletonLoader::LoadSkeleton(tinyxml2::XMLElement* pRoot, CSkeleton* pSkeleton) {
	// bones
	tinyxml2::XMLElement* pBones = pRoot->FirstChildElement("bones");
	if (!pBones) {
        XELOG("parse skeleton no find bones error");
		return false;
	}
	int id = 0;
	for (; pBones; pBones = pBones->NextSiblingElement()) {
		CBone* pBone = XENEW(CBone);
		pBone->m_nID = id++;
		const char* name = pBones->Attribute("name");
        tinyxml2::XMLElement* pChild = pBones->FirstChildElement();
		for (; pChild; pChild = pChild->NextSiblingElement()) {
			if (0 == strcmp(pChild->Value(), "position")) {
				float x = pChild->FloatAttribute("x");
				float y = pChild->FloatAttribute("y");
				float z = pChild->FloatAttribute("z");
				pBone->m_Init.pos.Set(x, y, z);
			} else if (0 == strcmp(pChild->Value(), "rotation")) {
				tinyxml2::XMLElement* axis = pChild->FirstChildElement("axis");
				float angle = pChild->FloatAttribute("angle");
				float x = axis->FloatAttribute("x");
				float y = axis->FloatAttribute("y");
				float z = axis->FloatAttribute("z");
				pBone->m_Init.rot.FromAngleAxis(angle, x, y, z);
			}
			pBone->m_Pose = pBone->m_Init;
		}
		pSkeleton->AddBone(name, pBone);
	}
    CSkeleton::BoneMap& BoneMap = pSkeleton->GetBoneMap();

	// bonehierarchy
	tinyxml2::XMLElement* pBonehierarchy = pRoot->FirstChildElement("bonehierarchy");
	if (!pBonehierarchy) {
        XELOG("parse skeleton no find bonehierarchy error");
		return false;
	}
	size_t i = 0;
    tinyxml2::XMLElement* pChild = pBonehierarchy->FirstChildElement();
	for (; pChild; pChild = pChild->NextSiblingElement()) {
		const char* name = pChild->Attribute("bone");
		const char* parent = pChild->Attribute("parent");
		auto iteParent = BoneMap.find(parent);
		auto iteChild = BoneMap.find(name);
		if (BoneMap.end() == iteChild || BoneMap.end() == iteParent) {
            XELOG("parse skeleton no find bonehierarchy2 error");
			return false;
		}
		iteChild->second->m_pParent = iteParent->second;
		iteChild->second->m_pNext = iteParent->second->m_pChild;
		iteParent->second->m_pChild = iteChild->second;
		++i;
	}
	// 存在2根以上父节点为空的骨骼
	if (BoneMap.size()-1 != i) {
        XELOG("parse skeleton root bone too more error");
		return false;
	}
	auto ite = BoneMap.begin();
	auto end = BoneMap.end();
	for (; end!=ite; ++ite) {
		if (!ite->second->m_pParent) {
			pSkeleton->SetRootBone(ite->second);
			break;
		}
	}
	
	// animations
	tinyxml2::XMLElement* pAnimations = pRoot->FirstChildElement("animations");
	if (!pAnimations) {
        XELOG("parse skeleton no find animations error");
		return false;
	}
	if (!LoadActions(pAnimations, pSkeleton)) {
        XELOG("parse skeleton parse animations error");
		return false;
	}

	// set bone pose
    pSkeleton->InitPose();

	return true;
}

bool CSkeletonLoader::LoadActions(tinyxml2::XMLElement* pActions, CSkeleton* pSkeleton) {
    tinyxml2::XMLElement* pChild = pActions->FirstChildElement();
    for (; pChild; pChild = pChild->NextSiblingElement()) {
		CAction* pAction = XENEW(CAction);
		const char* szName = LoadAction(pChild, pSkeleton, pAction);
		if (szName) {
			pSkeleton->AddAction(szName, pAction);
		} else {
			delete pAction;
            return false;
		}
	}
	return true;
}

const char* CSkeletonLoader::LoadAction(tinyxml2::XMLElement* pXml, CSkeleton* pSkeleton, CAction* pAction) {
	CAction::CKeyList KeyFrameList;

	// animation
	const char* szName = pXml->Attribute("name");
    if (!szName) {
        XELOG("parse skeleton no find action name error");
        return NULL;
    }
	float len = pXml->FloatAttribute("length");
    int nTime = CTimer::Time2Frame(len);
    pAction->Init(nTime);

	// track
    tinyxml2::XMLElement* pTrack = pXml->FirstChildElement("tracks")->FirstChildElement();
	for (; pTrack; pTrack = pTrack->NextSiblingElement()) {
		int nID = pSkeleton->GetBoneID(pTrack->Attribute("bone"));
		KeyFrameList.clear();

		// keyframe
        tinyxml2::XMLElement* pKeyFrameXml = pTrack->FirstChildElement("keyframes")->FirstChildElement();
		for (; pKeyFrameXml; pKeyFrameXml = pKeyFrameXml->NextSiblingElement()) {
			CAction::CKeyFrame* pKeyFrame = XENEW(CAction::CKeyFrame);
			float time = pKeyFrameXml->FloatAttribute("time");

			tinyxml2::XMLElement* pTranslate = pKeyFrameXml->FirstChildElement("translate");

			pKeyFrame->m_nTime = CTimer::Time2Frame(time);
			pKeyFrame->m_Pos.x = pTranslate->FloatAttribute("x");
			pKeyFrame->m_Pos.y = pTranslate->FloatAttribute("y");
			pKeyFrame->m_Pos.z = pTranslate->FloatAttribute("z");

			tinyxml2::XMLElement* pTmpElement = pKeyFrameXml->FirstChildElement("rotate");
			float angle = pTmpElement->FloatAttribute("angle");

			pTmpElement = pTmpElement->FirstChildElement("axis");
			float x = pTmpElement->FloatAttribute("x");
			float y = pTmpElement->FloatAttribute("y");
			float z = pTmpElement->FloatAttribute("z");

			pKeyFrame->m_Rot.FromAngleAxis(angle, x, y, z);
			KeyFrameList.XEPUSH(pKeyFrame);
		}

		pAction->Insert(nID, KeyFrameList);
	}
	return szName;
}

}
