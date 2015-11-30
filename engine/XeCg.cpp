#include "stdafx.h"
#include "XeCg.h"
#include "XeXFile.h"

namespace XE {

CCg::CCg() : m_nShaderID(0) {

}

CCg::~CCg() {
    FreeList<CCgParam>(m_EnvParamList);
	FreeList<CCgParam>(m_TargetParamList);

	if (0 != m_nShaderID) {
		glDeleteShader(m_nShaderID);
	}
}

void CCg::OnComplete(GLuint nProgramID) {
	auto ite = m_EnvParamList.begin();
	auto end = m_EnvParamList.end();
	for (; end!=ite; ++ite) {
		(*ite)->Init(nProgramID);
	}
	auto ite1 = m_TargetParamList.begin();
	auto end1 = m_TargetParamList.end();
	for (; end1!=ite1; ++ite1) {
		(*ite1)->Init(nProgramID);
	}
}
		
bool CCg::Read(ECgType eType, const char* szPath) {
	bool bRet = false;
	switch (eType) {
	case E_CgVertex:
		bRet = Init(GL_VERTEX_SHADER, szPath);
		break;

	case E_CgFragment:
		bRet = Init(GL_FRAGMENT_SHADER, szPath);
		break;

	default:
		break;
	}
	return bRet;
}

void CCg::Reset() {
	m_nShaderID = 0;
}

void CCg::Bind(IRenderEnv* pEnv) {
	auto ite = m_EnvParamList.begin();
	auto end = m_EnvParamList.end();
	for (; end!=ite; ++ite) {
		(*ite)->SetEnv(pEnv);
	}
}

void CCg::UnBind() {

}

void CCg::SetTarget(IRenderTarget* pTarget) {
   	auto ite = m_TargetParamList.begin();
	auto end = m_TargetParamList.end();
	for (; end!=ite; ++ite) {
		(*ite)->SetTarget(pTarget);
	}
}
	
void CCg::AddParam(CCgParam* p) {
	switch (p->GetType()) {
	case E_LightMatrix:
	case E_EyePosition:
	case E_AmbiColor:
	case E_LightColor:
	case E_LightPosition:
	case E_SampDepth:
		m_EnvParamList.XEPUSH(p);
		break;

	case E_ModelViewProj:
	case E_MaterialDiffuse:
	case E_MaterialAmbient:
	case E_MaterialSpecular:
	case E_MaterialEmissive:
	case E_Samp0:
		m_TargetParamList.XEPUSH(p);
		break;

	default:
		break;
	}
}

GLuint CCg::GetShaderID() {
	return m_nShaderID;
}
		
bool CCg::Init(GLenum type, const char* szPath) {
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CXFile::ReadFile(szPath, buffer, size)) {
		return false;
	}

	m_nShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_nShaderID, 1, (const GLchar**)&buffer, NULL);
	glCompileShader(m_nShaderID);

	GLint bCompile;
	glGetShaderiv(m_nShaderID, GL_COMPILE_STATUS, &bCompile);
	if (!bCompile) {
		GLint maxLength = 0;
		glGetShaderiv(m_nShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(m_nShaderID, maxLength, &maxLength, &infoLog[0]);

		std::string str(infoLog.begin(), infoLog.end());
		XELOG("glsl err shader: %s\n%s\n", szPath, str.c_str());

		XEDELETE(buffer);
		return false;
	}

	XEDELETE(buffer);
	return true;
}

}
