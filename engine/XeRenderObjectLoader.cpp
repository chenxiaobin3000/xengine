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
		XELOG("error: load render object: %s", szPath);
		return NULL;
	}

	tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.Parse((const char*)buffer);
    if (error != tinyxml2::XML_SUCCESS) {
        XELOG("error: parse render object: %d, %s", error, szPath);
        return NULL;
    }

	tinyxml2::XMLElement* root = doc.RootElement();
	if (!root) {
		XELOG("error: parse render object get root: %s", szPath);
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
        XELOG("error: parse render object no find geometry: %s", szPath);
		XEDELETE(pRenderObject);
        return NULL;
    }
	if (!LoadSharedGeometry(pGeometry, pVertexBuffer)) {
		XELOG("error: parse render object load geometry: %s", szPath);
		XEDELETE(pRenderObject);
        return NULL;
	}

    // mesh
    tinyxml2::XMLElement* pMesh = root->FirstChildElement("submeshes")->FirstChildElement("submesh");
    if (!pMesh) {
        XELOG("error: parse render object no find mesh: %s", szPath);
        XEDELETE(pRenderObject);
        return NULL;
    }
    if (!LoadMesh(pMesh, pRenderObject, pVertexBuffer)) {
        XELOG("error: parse render object load mesh: %s", szPath);
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
		XELOG("error: parse render object no find vertex buffer");
		return false;
	}
    if (!pVertexBuffer->SetVertexCount(nVertex)) {
        XELOG("error: parse render object set vertex count");
		return false;
    }

    float* pVertexs = NULL;
    float* pTexCoords = NULL;
    float* pNormals = NULL;
    unsigned int* pIndexs = NULL;
    if (!pVertexBuffer->Lock(pVertexs, pTexCoords, pNormals, pIndexs)) {
        XELOG("error: parse render object lock vertex");
		return false;
    }    

	// vertex
	tinyxml2::XMLElement* pVertex = pVertexBufferXml->FirstChildElement("vertex");
	if (!pVertex) {
		XELOG("error: parse render object no find vertex");
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
       		XELOG("error: parse render object no find position");
            return false;
        }

		// normal
		tinyxml2::XMLElement* pNormal = pVertex->FirstChildElement("normal");
		if (pNormal) {
			pNormals[i*3] = pNormal->FloatAttribute("x");
			pNormals[i*3+1] = pNormal->FloatAttribute("y");
			pNormals[i*3+2] = pNormal->FloatAttribute("z");
		} else {
       		XELOG("error: parse render object no find normal");
            return false;
        }

		// texcoord
		tinyxml2::XMLElement* pTexcoord = pVertex->FirstChildElement("texcoord");
		if (pTexcoord) {
			pTexCoords[i*2] = pTexcoord->FloatAttribute("u");
			pTexCoords[i*2+1] = pTexcoord->FloatAttribute("v");
		} else {
       		XELOG("error: parse render object no find position");
            return false;
        }
	}

    pVertexBuffer->Unlock();
	return true;
}

bool CRenderObjectLoader::LoadMesh(tinyxml2::XMLElement* pMesh, CRenderObject* pRenderObject, CVertexBuffer* pVertexBuffer) {
    // material
    const char* szMaterial = pMesh->Attribute("material");
    if (!szMaterial) {
        XELOG("error: parse render object no find material");
        return false;
    }
    CMaterial* pMaterial = CMaterialLoader::Load(szMaterial);
    if (!pMaterial) {
        XELOG("error: parse render object load material");
        return false;
    }
    pRenderObject->SetMaterial(pMaterial);
    
    // faces
    tinyxml2::XMLElement* pFaces = pMesh->FirstChildElement("faces");
    if (!pFaces) {
        XELOG("error: parse render object no find face");
        return false;
    }
    int nFaces = pFaces->IntAttribute("count");

    if (!pVertexBuffer->SetIndexCount(nFaces)) {
        XELOG("error: parse render object set index count");
        return false;
    }
    
    float* pVertexs = NULL;
    float* pTexCoords = NULL;
    float* pNormals = NULL;
    unsigned int* pIndexs = NULL;
    if (!pVertexBuffer->Lock(pVertexs, pTexCoords, pNormals, pIndexs)) {
        XELOG("error: parse render object lock index");
		return false;
    }    

    tinyxml2::XMLElement* pChild = pFaces->FirstChildElement("face");
    if (!pChild) {
        XELOG("error: parse render object no find index count face");
        return false;
    }
    for (int i=0; pChild; ++i, pChild = pChild->NextSiblingElement()) {
        pIndexs[i*3] = pChild->IntAttribute("v1");
        pIndexs[i*3+1] = pChild->IntAttribute("v2");
        pIndexs[i*3+2] = pChild->IntAttribute("v3");
    }

    //pRenderBuffer->Unlock(); 不需要解锁
	return true;
}

}
