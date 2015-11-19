#include "stdafx.h"
#include "XeGlesCgParam.h"
#include "XeGlesRenderSystem.h"
#include "XeGlesTexture.h"
#include "XeGlesCg.h"
#include "XePass.h"
#include "XeLight.h"
#include "XeScene.h"
#include "XeXmlLabel.h"

#ifdef PLATFORM_OPENGLES

namespace XE {

CGlesCgParam::CGlesCgParam() : m_nParamID(-1) {

}

CGlesCgParam::~CGlesCgParam() {

}

bool CGlesCgParam::InitParamID(GLuint nProgramID) {
	bool bRet = true;
	switch (m_eSetType) {
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

	case E_MaterialD:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_D);
		break;

	case E_MaterialA:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_A);
		break;

	case E_MaterialS:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_S);
		break;

	case E_MaterialE:
		m_nParamID = glGetUniformLocation(nProgramID, XML_MATERIAL_E);
		break;

	case E_FogColor:
		m_nParamID = glGetUniformLocation(nProgramID, XML_FOG_COLOR);
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

bool CGlesCgParam::SetParam(CPass* pPass) {
	if (-1 == m_nParamID) {
		return false;
	}

	float tmp[4];
	bool bRet = true;
	switch (m_eSetType) {
	case E_ModelViewProj:
		glUniformMatrix4fv(m_nParamID, 1, GL_FALSE, pPass->m_Matrix.m);
		break;

	case E_LightMatrix:
		glUniformMatrix4fv(m_nParamID, 1, GL_FALSE, pPass->m_LightMatrix.m);
		break;

	case E_EyePosition:
		tmp[0] = pPass->m_EyePosition.x; tmp[1] = pPass->m_EyePosition.y;
		tmp[2] = pPass->m_EyePosition.z;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_AmbiColor:
		tmp[0] = pPass->m_AmbientColor.r; tmp[1] = pPass->m_AmbientColor.g;
		tmp[2] = pPass->m_AmbientColor.b;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_LightColor:
		{
			CColor_f* p = (CColor_f*)pPass->GetLightColor();
			if (p) {
				tmp[0] = p->r; tmp[1] = p->g; tmp[2] = p->b;
				glUniform3fv(m_nParamID, 1, tmp);
			}
		}
		break;

	case E_LightPosition:
		{
			CColor_f* p = (CColor_f*)pPass->GetLightPosition();
			if (p) {
				tmp[0] = p->r; tmp[1] = p->g; tmp[2] = p->b;
				glUniform3fv(m_nParamID, 1, tmp);
				pPass->IncLightIndex();
			}
		}
		break;

	case E_MaterialD:
		tmp[0] = pPass->m_DiffuseM.r; tmp[1] = pPass->m_DiffuseM.g;
		tmp[2] = pPass->m_DiffuseM.b; tmp[3] = pPass->m_DiffuseM.a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_MaterialA:
		tmp[0] = pPass->m_AmbientM.r; tmp[1] = pPass->m_AmbientM.g;
		tmp[2] = pPass->m_AmbientM.b; tmp[3] = pPass->m_AmbientM.a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_MaterialS:
		tmp[0] = pPass->m_SpecularM.r; tmp[1] = pPass->m_SpecularM.g;
		tmp[2] = pPass->m_SpecularM.b; tmp[3] = pPass->m_SpecularM.a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_MaterialE:
		tmp[0] = pPass->m_EmissiveM.r; tmp[1] = pPass->m_EmissiveM.g;
		tmp[2] = pPass->m_EmissiveM.b; tmp[3] = pPass->m_EmissiveM.a;
		glUniform4fv(m_nParamID, 1, tmp);
		break;

	case E_FogColor:
		tmp[0] = pPass->m_FogColor.r; tmp[1] = pPass->m_FogColor.g;
		tmp[2] = pPass->m_FogColor.b;
		glUniform3fv(m_nParamID, 1, tmp);
		break;

	case E_Samp0:
		{
			glActiveTexture(GL_TEXTURE0);
			CGlesTexture* pTexture = (CGlesTexture*)pPass->GetTexture();
			pTexture->Bind(CTexture::E_Normal);
			glUniform1i(m_nParamID, 0);
		}
		break;

	case E_SampDepth:
		{
			glActiveTexture(GL_TEXTURE1);
			CGlesTexture* pTexture = (CGlesTexture*)pPass->GetDepthTexture();
			pTexture->Bind(CTexture::E_Depth);
			glUniform1i(m_nParamID, 1);
		}
		break;

	default:
		bRet = false;
	}
	return bRet;
}

}

#endif //PLATFORM_OPENGLES
