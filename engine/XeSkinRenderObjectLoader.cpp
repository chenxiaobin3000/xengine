#include "stdafx.h"
#include "XeSkinRenderObjectLoader.h"

namespace XE {

CSkinRenderObjectLoader::CSkinRenderObjectLoader() {
	
}

CSkinRenderObjectLoader::~CSkinRenderObjectLoader() {
	
}

CRenderObject* CSkinRenderObjectLoader::Load(const char* szName) {

}

bool CSkinRenderObjectLoader::LoadXml(const char* szPath) {
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CXFile::ReadText(szPath, buffer, size)) {
		XELOG("load skin render object error: %s\n", szPath);
		return false;
	}

	TiXmlDocument doc;
	if (!doc.Parse((const char*)buffer)) {
		XELOG("parse skin render object error: %s\n", szPath);
		return false;
	}
	TiXmlElement* root = doc.RootElement();
	if (!root) {
		return false;
	}

	// sharedgeometry
	TiXmlNode* pNode = root->FirstChild("sharedgeometry");
	if (pNode) {
		if (!LoadSharedGeometry(pNode->ToElement())) {
			return false;
		}
	}

	// submeshes
	pNode = root->FirstChild("submeshes");
	if (!pNode) {
		return false;
	}
	if (!LoadMesh(pNode)) {
		return false;
	}

	// material
	m_strMaterialName = m_list[0]->GetMaterialName();

	// skeleton
	pNode = root->FirstChild("skeletonlink");
	if (pNode) {
		m_bSkeleton = true;
		m_strSkeletonName = pNode->ToElement()->Attribute("name");
	}

	// boneassignments
	pNode = root->FirstChild("boneassignments");
	if (pNode) {
		LoadBoneAssignments(pNode->ToElement());
	}

	return true;
}

bool CSkinRenderObjectLoader::LoadMesh(TiXmlNode* pMeshes) {
	bool bRet = false;
	TiXmlNode* pChild;
	for (pChild = pMeshes->FirstChild(); pChild; pChild = pChild->NextSibling()) {
		if (0 == strcmp(pChild->Value(), "submesh")) {
			CSubMesh* pMesh = NEW_LOG(CSubMesh);
			if (pMesh->LoadSubMesh(pChild->ToElement())) {
				Insert(pMesh);
				bRet = true;
			} else {
				delete pMesh;
			}
		}
	}
	return bRet;
}

bool CSkinRenderObjectLoader::LoadSharedGeometry(TiXmlElement* pGeometry) {
	TiXmlNode*		pChild;
	TiXmlNode*		pSubChild;
	TiXmlNode*		pTmpNode;
	TiXmlElement*	pChildElement;
	double			dValue;
	CVertex			vertex;
	CPoint			point;

	//geometry
	int nVertex = atoi(pGeometry->Attribute("vertexcount"));
	for (pChild = pGeometry->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		TiXmlElement* pVertexbuffer = pChild->ToElement();
		if (0 != strcmp(pVertexbuffer->Value(), "vertexbuffer")) {
			continue;
		}
		if (pVertexbuffer->Attribute("positions")) {
			for (pSubChild = pVertexbuffer->FirstChild(); pSubChild; pSubChild = pSubChild->NextSibling()) {
				//positions
				pChildElement = pSubChild->ToElement()->FirstChild("position")->ToElement();
				pChildElement->Attribute(XML_X, &dValue);		vertex.x = (float)dValue;
				pChildElement->Attribute(XML_Y, &dValue);		vertex.y = (float)dValue;
				pChildElement->Attribute(XML_Z, &dValue);		vertex.z = (float)dValue;
				m_PosList.PUSH(vertex);

				//normals
				pChildElement = pSubChild->ToElement()->FirstChild("normal")->ToElement();
				pChildElement->Attribute(XML_X, &dValue);		vertex.x = (float)dValue;
				pChildElement->Attribute(XML_Y, &dValue);		vertex.y = (float)dValue;
				pChildElement->Attribute(XML_Z, &dValue);		vertex.z = (float)dValue;
				m_NorList.PUSH(vertex);

				//coords
				pTmpNode = pSubChild->ToElement()->FirstChild("texcoord");
				if (pTmpNode) {
					pChildElement = pTmpNode->ToElement();
					pChildElement->Attribute(XML_U, &dValue);		point.x = (float)dValue;
					pChildElement->Attribute(XML_V, &dValue);		point.y = (float)dValue;
					m_TexList.PUSH(point);
				}
			}
		}

		//texture_coords
		else if (pVertexbuffer->Attribute("texture_coords")) {
			for (pSubChild = pVertexbuffer->FirstChild(); pSubChild; pSubChild = pSubChild->NextSibling()) {
				pChildElement = pSubChild->ToElement()->FirstChild("texcoord")->ToElement();
				pChildElement->Attribute(XML_U, &dValue);		point.x = (float)dValue;
				pChildElement->Attribute(XML_V, &dValue);		point.y = (float)dValue;
				m_TexList.PUSH(point);
			}
		}
	}

	if (nVertex != m_PosList.size()
	||  nVertex != m_NorList.size()
	||  nVertex != m_TexList.size()) {
		return false;
	}
	return true;
}

bool CSkinRenderObjectLoader::LoadBoneAssignments(TiXmlElement* pBoneAssignments) {
	TiXmlNode*		pChild;
	TiXmlElement*	pChildElement;
	double			dValue;
	int				nVID;
	int				nBID;
	for (pChild = pBoneAssignments->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		pChildElement = pChild->ToElement();
		pChildElement->Attribute("vertexindex", &nVID);
		pChildElement->Attribute("boneindex", &nBID);
		pChildElement->Attribute("weight", &dValue);
		if (dValue > CSubMesh::s_fSkinMin) {
			m_SkinAssign.Insert(nVID, nBID, (float)dValue);
		}
	}
	return true;
}

}
