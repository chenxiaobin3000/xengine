#include "stdafx.h"
#include "XeRenderObjectLoader.h"
#include "XeMaterialLoader.h"
#include "XeVertexBuffer.h"
#include "XeFaceIndex.h"
#include "XeXFile.h"

namespace XE {

CRenderObjectLoader::CRenderObjectLoader() {

}

CRenderObjectLoader::~CRenderObjectLoader() {

}

CRenderObject* CRenderObjectLoader::Load(const char* szName) {
    std::string str = "mesh/";
    str += szName;
    return LoadXml(str.c_str());
}

CRenderObject* CRenderObjectLoader::LoadXml(const char* szPath) {
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CXFile::ReadText(szPath, buffer, size)) {
		XELOG("load render object error: %s", szPath);
		return NULL;
	}

	tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse((const char*)buffer);
    if (error != tinyxml2::XML_SUCCESS) {
        XELOG("parse render object error: %d, %s", error, szPath);
        return NULL;
    }

	tinyxml2::XMLElement* root = doc.RootElement();
	if (!root) {
		XELOG("parse render object get root error: %s", szPath);
		return NULL;
	}

    // renderbuffer
    CVertexBuffer* pVertexBuffer = XENEW(CVertexBuffer);
    if (!pVertexBuffer) {
        return NULL;
    }

 	CRenderObject* pRenderObject = XENEW(CRenderObject);
    if (!pRenderObject) {
        XEDELETE(pVertexBuffer);
        return NULL;
    }
    pRenderObject->SetVertexBuffer(pVertexBuffer);

    // sharedgeometry
	tinyxml2::XMLElement* pGeometry = root->FirstChildElement("sharedgeometry");
    if (!pGeometry) {
        XELOG("parse render object no find geometry error: %s", szPath);
		XEDELETE(pRenderObject);
        return NULL;
    }
	if (!LoadSharedGeometry(pGeometry, pVertexBuffer)) {
		XELOG("parse render object load geometry error: %s", szPath);
		XEDELETE(pRenderObject);
        return NULL;
	}

    // mesh
    tinyxml2::XMLElement* pMesh = root->FirstChildElement("submeshes")->FirstChildElement("submesh");
    if (!pMesh) {
        XELOG("parse render object no find mesh error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }
    if (!LoadMesh(pMesh, pRenderObject, pVertexBuffer)) {
        XELOG("parse render object load mesh error: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }

	return pRenderObject;
}

bool CRenderObjectLoader::LoadSharedGeometry(tinyxml2::XMLElement* pGeometry, CVertexBuffer* pVertexBuffer) {
	// vertexcount
	int nVertex = atoi(pGeometry->Attribute("vertexcount"));
	tinyxml2::XMLElement* pVertexBufferXml = pGeometry->FirstChildElement("vertexbuffer");
	if (!pVertexBufferXml) {
		XELOG("parse render object no find vertex buffer error");
		return false;
	}
    if (!pVertexBuffer->SetVertexCount(nVertex)) {
        XELOG("parse render object set vertex count error");
		return false;
    }

    float* pVertexs = NULL;
    float* pTexCoords = NULL;
    float* pNormals = NULL;
    unsigned int* pIndexs = NULL;
    if (!pVertexBuffer->Lock(pVertexs, pTexCoords, pNormals, pIndexs)) {
        XELOG("parse render object lock vertex error");
		return false;
    }    

	// vertex
	tinyxml2::XMLElement* pVertex = pVertexBufferXml->FirstChildElement("vertex");
	if (!pVertex) {
		XELOG("parse render object no find vertex error");
		return false;
	}

    pVertex = pVertexBufferXml->FirstChildElement("vertex");
	for (int i=0; pVertex; ++i, pVertex = pVertex->NextSiblingElement()) {
		// position
		tinyxml2::XMLElement* pPosition = pVertex->FirstChildElement("position");
		if (pPosition) {
			pVertexs[i*3] = pPosition->FloatAttribute("x");
			pVertexs[i*3+1] = pPosition->FloatAttribute("y");
			pVertexs[i*3+2] = pPosition->FloatAttribute("z");
		} else {
       		XELOG("parse render object no find position error");
            return false;
        }

		// normal
		tinyxml2::XMLElement* pNormal = pVertex->FirstChildElement("normal");
		if (pNormal) {
			pNormals[i*3] = pNormal->FloatAttribute("x");
			pNormals[i*3+1] = pNormal->FloatAttribute("y");
			pNormals[i*3+2] = pNormal->FloatAttribute("z");
		} else {
       		XELOG("parse render object no find normal error");
            return false;
        }

		// texcoord
		tinyxml2::XMLElement* pTexcoord = pVertex->FirstChildElement("texcoord");
		if (pTexcoord) {
			pTexCoords[i*2] = pTexcoord->FloatAttribute("u");
			pTexCoords[i*2+1] = pTexcoord->FloatAttribute("v");
		} else {
       		XELOG("parse render object no find position error");
            return false;
        }
	}

    pVertexBuffer->Unlock();
	return true;
}

bool CRenderObjectLoader::LoadMesh(tinyxml2::XMLElement* pMesh, CRenderObject* pRenderObject, CVertexBuffer* pVertexBuffer) {
	bool bRet = false;
    
    // material
    const char* szMaterial = pMesh->Attribute("material");
    if (!szMaterial) {
        XELOG("parse render object no find material error");
        return false;
    }
    CMaterial* pMaterial = CMaterialLoader::Load(szMaterial);
    if (!pMaterial) {
        XELOG("parse render object load material error");
        return false;
    }
    pRenderObject->SetMaterial(pMaterial);
    
    // faces
    tinyxml2::XMLElement* pFaces = pMesh->FirstChildElement("faces");
    if (!pFaces) {
        XELOG("parse render object no find face error");
        return false;
    }
    int nFaces = pFaces->IntAttribute("count");

    if (!pVertexBuffer->SetIndexCount(nFaces)) {
        XELOG("parse render object set index count error");
        return false;
    }
    
    float* pVertexs = NULL;
    float* pTexCoords = NULL;
    float* pNormals = NULL;
    unsigned int* pIndexs = NULL;
    if (!pVertexBuffer->Lock(pVertexs, pTexCoords, pNormals, pIndexs)) {
        XELOG("parse render object lock index error");
		return false;
    }    

    tinyxml2::XMLElement* pChild = pFaces->FirstChildElement("vertex");
    for (int i=0; pChild; ++i, pChild = pChild->NextSiblingElement()) {
        pIndexs[i*3] = pChild->IntAttribute("v1");
        pIndexs[i*3+1] = pChild->IntAttribute("v2");
        pIndexs[i*3+2] = pChild->IntAttribute("v3");
    }

    //pRenderBuffer->Unlock(); 不需要解锁
	return bRet;
}

}
