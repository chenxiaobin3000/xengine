#include "stdafx.h"
#include "XeSkinRenderObjectLoader.h"
#include "XeSkeletonLoader.h"
#include "XeXFile.h"

namespace XE {

const float CSkinRenderObjectLoader::s_fSkinMin = 0.01f;

CSkinRenderObjectLoader::CSkinRenderObjectLoader() {

}

CSkinRenderObjectLoader::~CSkinRenderObjectLoader() {
	
}

CSkinRenderObject* CSkinRenderObjectLoader::Load(const char* szName) {
    return NULL;
}

bool CSkinRenderObjectLoader::LoadXml(const char* szPath) {
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CXFile::ReadText(szPath, buffer, size)) {
		XELOG("load skin render object error: %s\n", szPath);
		return false;
	}

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse((const char*)buffer);
    if (error != tinyxml2::XML_SUCCESS) {
		XELOG("parse skin render object error: %s\n", szPath);
		return false;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	if (!root) {
		return false;
	}

    // renderbuffer
	CVertexBuffer* pVertexBuffer = XENEW(CVertexBuffer);
    if (!pVertexBuffer) {
        return NULL;
    }

 	CSkinRenderObject* pRenderObject = XENEW(CSkinRenderObject);
    if (!pRenderObject) {
        XEDELETE(pVertexBuffer);
        return NULL;
    }
    pRenderObject->SetVertexBuffer(pVertexBuffer);

    // sharedgeometry
	tinyxml2::XMLElement* pGeometry = root->FirstChildElement("sharedgeometry");
	if (!pGeometry) {
        XELOG("parse skin render object no find geometry error: %s", szPath);
		XEDELETE(pRenderObject);
        return NULL;
	}
    if (!LoadSharedGeometry(pGeometry, pVertexBuffer)) {
        XELOG("parse skin render object load geometry error: %s", szPath);
		XEDELETE(pRenderObject);
        return NULL;
    }

	// mesh
    tinyxml2::XMLElement* pMesh = root->FirstChildElement("submeshes")->FirstChildElement("submesh");
    if (!pMesh) {
        XELOG("parse skin render object no find mesh error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }
    if (!LoadMesh(pMesh, pRenderObject, pVertexBuffer)) {
        XELOG("parse skin render object load mesh error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }

	// skeleton
	tinyxml2::XMLElement* pSkeletonLink = root->FirstChildElement("skeletonlink");
	if (!pSkeletonLink) {
        XELOG("parse skin render object no find skeleton link error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }
	const char* szSkeletonName = pSkeletonLink->Attribute("name");
    if (!szSkeletonName) {
        XELOG("parse render object no find skeleton error");
        return NULL;
    }
    CSkeleton* pSkeleton = CSkeletonLoader::Load(szSkeletonName);
    if (!pSkeleton) {
        XELOG("parse render object load material error");
        return NULL;
    }
    pRenderObject->SetSkeleton(pSkeleton);

	// boneassignments
	tinyxml2::XMLElement* pBoneAssignments = root->FirstChildElement("boneassignments");
	if (!pBoneAssignments) {
        XELOG("parse skin render object no find bone error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }
    if (!LoadBoneAssignments(pBoneAssignments, pRenderObject)) {
        XELOG("parse skin render object load bone error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
	}

	return true;
}

bool CSkinRenderObjectLoader::LoadBoneAssignments(tinyxml2::XMLElement*  pBoneAssignments, CSkinRenderObject* pRenderObject) {
    CSkinAssign& list = pRenderObject->GetSkinAssign();
    tinyxml2::XMLElement* pBone = pBoneAssignments->FirstChildElement();
    for (; pBone; pBone = pBone->NextSiblingElement()) {
        int nBID = pBone->IntAttribute("boneindex");
        int nVID = pBone->IntAttribute("vertexindex");
        float fWeight = pBone->FloatAttribute("weight");
        if (fWeight > s_fSkinMin) {
			list.Insert(nVID, nBID, fWeight);
		}
    }
    
	return true;
}

}
