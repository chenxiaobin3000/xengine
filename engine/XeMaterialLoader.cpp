#include "stdafx.h"
#include "XeMaterialLoader.h"
#include "XeXFile.h"
#include "XeJson.h"

namespace XE {

CMaterialLoader::CMaterialLoader() {

}

CMaterialLoader::~CMaterialLoader() {

}

CMaterial* CMaterialLoader::Load(const char* szName) {
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CXFile::ReadText(szName, buffer, size)) {
        XELOG("material file error: %s", szName);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse((const char*)buffer, root)) {
        XELOG("material parse error: %s", szName);
		XEDELETE(buffer);
		return NULL;
	}
    XEDELETE(buffer);
    
    for (int i=0; i<root.size(); ++i) {
        Json::Value& value = root[i];
        std::string type = value["type"].asString();
        printf("%s\n", type.c_str());
    }
    
    Json::Value material = CJson::GetByType(root, "material");
    if (material.isNull()) {
        XELOG("material not find material: %s", szName);
        return NULL;
    }
    
    CMaterial* pMaterial = XENEW(CMaterial);
    if (!pMaterial) {
        return NULL;
    }
    
    // 技术列表，目前只解析一个
    Json::Value& t_list = material["list"];
    Json::Value& technique = t_list[0];
    
    CTechnique* pTechnique = XENEW(CTechnique);
    if (!pTechnique) {
        XEDELETE(pMaterial);
        return NULL;
    }
    pMaterial->SetTechnique(pTechnique);
    
    // 解析pass列表，目前只解析一个
    Json::Value& p_list = technique["list"];
    Json::Value& pass = p_list[0];
    
    // 解析pass
    CPass* pPass = ParsePass(pass, root);
    if (!pPass) {
        XEDELETE(pMaterial);
    }
    pTechnique->SetPass(pPass);
    
    return pMaterial;
}

CCg* CMaterialLoader::ParseVertex(const char* szName, Json::Value& root) {
    Json::Value vertex_program = CJson::GetByType(root, "vertex_program");
    if (vertex_program.isNull()) {
        XELOG("material not find vertex_program: %s", szName);
        return NULL;
    }

    Json::Value& list = vertex_program["list"];
    Json::Value sourceJson = CJson::GetByName(list, szName);
    const char* source = sourceJson["source"].asCString();
    
    CCg* pCg = new CCg;
    if (!pCg) {
        return NULL;
    }
    if (!pCg->Read(CCg::E_CgVertex, source)) {
        XELOG("material read vertex_program error: %s", szName);
        return NULL;
    }
    
    Json::Value& params = sourceJson["params"];
    for (int i=0; i<params.size(); ++i) {
        const char* value = params[i].asCString();
        CCgParam* param = XENEW(CCgParam(value));
        pCg->AddParam(param);
    }
    
    return pCg;
}

CCg* CMaterialLoader::ParseFragment(const char* szName, Json::Value& root) {
    Json::Value fragment_program = CJson::GetByType(root, "fragment_program");
    if (fragment_program.isNull()) {
        XELOG("material not find fragment_program: %s", szName);
        return NULL;
    }
    
    Json::Value& list = fragment_program["list"];
    Json::Value sourceJson = CJson::GetByName(list, szName);
    const char* source = sourceJson["source"].asCString();
    
    CCg* pCg = new CCg;
    if (!pCg) {
        return NULL;
    }
    if (!pCg->Read(CCg::E_CgFragment, source)) {
        XELOG("material read fragment_program error: %s", szName);
        return NULL;
    }
    
    Json::Value& params = sourceJson["params"];
    for (int i=0; i<params.size(); ++i) {
        const char* value = params[i].asCString();
        CCgParam* param = XENEW(CCgParam(value));
        pCg->AddParam(param);
    }
    
    return pCg;
}

CPass* CMaterialLoader::ParsePass(Json::Value& json, Json::Value& root) {
    const char* szVertexProgram = json["vertex_program"].asCString();
    const char* szFragmentProgram = json["fragment_program"].asCString();
    Json::Value& diffuseJson = json["diffuse"];
    Json::Value& ambientJson = json["ambient"];
    Json::Value& specularJson = json["specular"];
    Json::Value& emissiveJson = json["emissive"];
    Json::Value& textureUnitJson = json["texture_unit"];
    const char* texture = textureUnitJson["texture"].asCString();
    std::string filter_mode = textureUnitJson["filter_mode"].asString();
    std::string address_mode = textureUnitJson["address_mode"].asString();
    
    // 创建颜色
    CColorF diffuse = CColorF(diffuseJson[0].asFloat(),
                              diffuseJson[1].asFloat(),
                              diffuseJson[2].asFloat(),
                              diffuseJson[3].asFloat());
    
    CColorF ambient = CColorF(ambientJson[0].asFloat(),
                              ambientJson[1].asFloat(),
                              ambientJson[2].asFloat(),
                              ambientJson[3].asFloat());
    
    CColorF specular = CColorF(specularJson[0].asFloat(),
                               specularJson[1].asFloat(),
                               specularJson[2].asFloat(),
                               specularJson[3].asFloat());
    
    CColorF emissive = CColorF(emissiveJson[0].asFloat(),
                               emissiveJson[1].asFloat(),
                               emissiveJson[2].asFloat(),
                               emissiveJson[3].asFloat());
    
    // 创建纹理
    CTexture* pTexture = XENEW(CTexture);
    if (!pTexture) {
        return NULL;
    }
    
    if (filter_mode == "nearest") {
        pTexture->SetFilter(ITexture::E_Nearest);
    } else if (filter_mode == "linear") {
        pTexture->SetFilter(ITexture::E_Linear);
    }
    
    if (address_mode == "repeat") {
        pTexture->SetAddress(ITexture::E_Repeat);
    } else if (address_mode == "clamp") {
        pTexture->SetAddress(ITexture::E_Clamp);
    }
    
    if (!pTexture->Load(texture)) {
        XELOG("material parse pass load texture error: %s", texture);
        XEDELETE(pTexture);
        return NULL;
    }
    
    // 创建program
    CCgProgram* pProgram = XENEW(CCgProgram);
    if (!pProgram) {
        XEDELETE(pTexture);
        return NULL;
    }
    
    // 创建vertex
    CCg* pVertex = ParseVertex(szVertexProgram, root);
    if (!pVertex) {
        XELOG("material parse pass load vertex error: %s", szVertexProgram);
        XEDELETE(pTexture);
        XEDELETE(pProgram);
        return NULL;
    }
    pProgram->AddCg(pVertex);
    
    // 创建fragment
    CCg* pFragment = ParseFragment(szFragmentProgram, root);
    if (!pFragment) {
        XELOG("material parse pass load fragment error: %s", szFragmentProgram);
        XEDELETE(pTexture);
        XEDELETE(pProgram);
        XEDELETE(pVertex);
        return NULL;
    }
    pProgram->AddCg(pFragment);
    
    pProgram->Compile();
    
    // 创建pass
    CPass* pPass = XENEW(CPass);
    if (!pPass) {
        XEDELETE(pTexture);
        XEDELETE(pProgram);
        XEDELETE(pVertex);
        XEDELETE(pFragment);
        return NULL;
    }
    pPass->Init(pTexture, true, diffuse, ambient, specular, emissive, pProgram);
    return pPass;
}

}
