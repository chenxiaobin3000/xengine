#include "stdafx.h"
#include "XeCgParam.h"
#include "XePass.h"
#include "XeMatrix.h"
#include "XeColor.h"
#include "XeTexture.h"

#define XML_MODEL_VIEW_PROJ			"ModelViewProj"
#define XML_LIGHT_MATRIX			"LightMatrix"
#define XML_EYE_POSITION			"EyePosition"
#define XML_AMBI_COLOR				"AmbiColor"
#define XML_LIGHT_COLOR				"LightColor"
#define XML_LIGHT_POSITION			"LightPosition"
#define XML_MATERIAL_D				"MaterialD"
#define XML_MATERIAL_A				"MaterialA"
#define XML_MATERIAL_S				"MaterialS"
#define XML_MATERIAL_E				"MaterialE"
#define XML_SAMP0					"Samp0"
#define XML_SAMP_DEPTH				"SampDepth"

namespace XE {

CCgParam::CCgParam(const char* szType) : m_nParamID(-1), m_eType(E_ParamNum) {
	if (0 == strcmp(XML_MODEL_VIEW_PROJ, szType)) {
		m_eType = E_ModelViewProj;
	} else if (0 == strcmp(XML_LIGHT_MATRIX, szType)) {
		m_eType = E_LightMatrix;
	} else if (0 == strcmp(XML_EYE_POSITION, szType)) {
		m_eType = E_EyePosition;
	} else if (0 == strcmp(XML_AMBI_COLOR, szType)) {
		m_eType = E_AmbiColor;
	} else if (0 == strcmp(XML_LIGHT_COLOR, szType)) {
		m_eType = E_LightColor;
	} else if (0 == strcmp(XML_LIGHT_POSITION, szType)) {
		m_eType = E_LightPosition;
	} else if (0 == strcmp(XML_MATERIAL_D, szType)) {
		m_eType = E_MaterialDiffuse;
	} else if (0 == strcmp(XML_MATERIAL_A, szType)) {
		m_eType = E_MaterialAmbient;
	} else if (0 == strcmp(XML_MATERIAL_S, szType)) {
		m_eType = E_MaterialSpecular;
	} else if (0 == strcmp(XML_MATERIAL_E, szType)) {
		m_eType = E_MaterialEmissive;
	} else if (0 == strcmp(XML_SAMP0, szType)) {
		m_eType = E_Samp0;
	} else if (0 == strcmp(XML_SAMP_DEPTH, szType)) {
		m_eType = E_SampDepth;
	}
}

CCgParam::~CCgParam() {

}

bool CCgParam::Init(GLuint nProgramID) {
	if (E_ParamNum == m_eType) {
		return false;
	}
	
	bool bRet = true;
	switch (m_eType) {
	case E_ModelViewProj:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MODEL_VIEW_PROJ);
		break;

	case E_LightMatrix:
		m_nParamID = glGetUniformLocation(nProgramID, XML_LIGHT_MATRIX);
		break;

	case E_EyePosition:
		m_nParamID = glGetUniformLocation(nProgramID, XML_EYE_POSITION);
		break;

	case E_AmbiColor:
		m_nParamID = glGetUniformLocation(nProgramID, XML_AMBI_COLOR);
		break;

	case E_LightColor:
		m_nParamID = glGetUniformLocation(nProgramID, XML_LIGHT_COLOR);
		break;

	case E_LightPosition:
		m_nParamID = glGetUniformLocation(nProgramID, XML_LIGHT_POSITION);
		break;

	case E_MaterialDiffuse:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_D);
		break;

	case E_MaterialAmbient:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_A);
		break;

	case E_MaterialSpecular:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_S);
		break;

	case E_MaterialEmissive:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_E);
		break;

	case E_Samp0:
		m_nParamID = glGetUniformLocation(nProgramID, XML_SAMP0);
		break;

	case E_SampDepth:
		m_nParamID = glGetUniformLocation(nProgramID, XML_SAMP_DEPTH);
		break;

	default:
		bRet = false;
	}
	return bRet;
}

ECgParamType CCgParam::GetType() {
    return m_eType;
}
    
bool CCgParam::SetEnv(IRenderEnv* pEnv) {
	if (-1 == m_nParamID) {
		return false;
	}

	float tmp[4];
	CTexture* pTexture = NULL;
	bool bRet = true;
	switch (m_eType) {
	case E_LightMatrix:
		glUniformMatrix4fv(m_nParamID, 1, GL_FALSE, pEnv->GetLightMatrix().m);
		break;

	case E_EyePosition:
		tmp[0] = pEnv->GetEyePosition().x;
		tmp[1] = pEnv->GetEyePosition().y;
		tmp[2] = pEnv->GetEyePosition().z;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_AmbiColor:
		tmp[0] = pEnv->GetAmbientColor().r;
		tmp[1] = pEnv->GetAmbientColor().g;
		tmp[2] = pEnv->GetAmbientColor().b;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_LightColor:
		tmp[0] = pEnv->GetLightColor().r;
		tmp[1] = pEnv->GetLightColor().g;
		tmp[2] = pEnv->GetLightColor().b;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_LightPosition:
		tmp[0] = pEnv->GetLightPosition().x;
		tmp[1] = pEnv->GetLightPosition().y;
		tmp[2] = pEnv->GetLightPosition().z;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_SampDepth:
		glActiveTexture(GL_TEXTURE1);
		pTexture = pEnv->GetDepthTexture();
		if (pTexture) {
			pTexture->Bind();
			glUniform1i(m_nParamID, E_SamplerShadow);
		}
		break;

	default:
		bRet = false;
	}
	return bRet;
}

bool CCgParam::SetTarget(IRenderTarget* pTarget) {
	if (-1 == m_nParamID) {
		return false;
	}

	bool bRet = true;
	switch (m_eType) {
	case E_ModelViewProj:
		glUniformMatrix4fv(m_nParamID, 1, GL_FALSE, pTarget->GetModelViewProj().m);
		break;

	default:
		bRet = false;
	}
	return bRet;
}

bool CCgParam::SetPass(CPass* pPass) {
	if (-1 == m_nParamID) {
		return false;
	}

	float tmp[4];
	CTexture* pTexture = NULL;
	bool bRet = true;
	switch (m_eType) {
	case E_MaterialDiffuse:
		tmp[0] = pPass->GetMaterialDiffuse().r;
		tmp[1] = pPass->GetMaterialDiffuse().g;
		tmp[2] = pPass->GetMaterialDiffuse().b;
		tmp[3] = pPass->GetMaterialDiffuse().a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_MaterialAmbient:
		tmp[0] = pPass->GetMaterialAmbient().r;
		tmp[1] = pPass->GetMaterialAmbient().g;
		tmp[2] = pPass->GetMaterialAmbient().b;
		tmp[3] = pPass->GetMaterialAmbient().a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_MaterialSpecular:
		tmp[0] = pPass->GetMaterialSpecular().r;
		tmp[1] = pPass->GetMaterialSpecular().g;
		tmp[2] = pPass->GetMaterialSpecular().b;
		tmp[3] = pPass->GetMaterialSpecular().a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_MaterialEmissive:
		tmp[0] = pPass->GetMaterialEmissive().r;
		tmp[1] = pPass->GetMaterialEmissive().g;
		tmp[2] = pPass->GetMaterialEmissive().b;
		tmp[3] = pPass->GetMaterialEmissive().a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_Samp0:
		glActiveTexture(GL_TEXTURE0);
		pTexture = pPass->GetTexture();
		if (pTexture) {
			pTexture->Bind();
			glUniform1i(m_nParamID, E_SamplerNormal);
		}
		break;

	default:
		bRet = false;
	}
	return bRet;
}
	
}
