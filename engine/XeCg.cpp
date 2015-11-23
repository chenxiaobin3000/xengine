#include "stdafx.h"
#include "XeCg.h"

namespace XE {

CCg::CCg() : m_nShaderID(0) {

}

CCg::~CCg() {
    FreeList<CCgParam>(m_CgParamList);

	if (0 != m_nShaderID) {
		glDeleteShader(m_nShaderID);
	}
}

bool CCg::Read(ECgType eType, const char* szPath, const char* szMain) {
	bool bRet = false;
	switch (eType) {
	case E_CgVertex:
		bRet = InitVertex(szPath);
		break;

	case E_CgFragment:
		bRet = InitFragment(szPath);
		break;

	default:
		break;
	}
	return bRet;
}

void CCg::Reset() {
	m_nShaderID = 0;
}

void CCg::Bind(CPass* pPass) {
	auto ite = m_CgParamList.begin();
	auto end = m_CgParamList.end();
	for (; end!=ite; ++ite) {
		(*ite)->SetParam(pPass);
	}
}

void CCg::UnBind() {

}

void CCg::AddParam(CCgParam* p) {
	m_CgParamList.PUSH(p);
}

void CCg::InitParam(GLuint nProgramID) {
	auto ite = m_CgParamList.begin();
	auto end = m_CgParamList.end();
	for (; end!=ite; ++ite) {
		((CCgParam*)(*ite))->InitParamID(nProgramID);
	}
}

bool CCg::InitVertex(const char* szPath) {
	CMemFile file;
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CResManager::LoadTxtFile(szPath, buffer, size, file)) {
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
		XELOG("glsl err vertex shader: %s\n%s\n", szPath, str.c_str());
		return false;
	}

	return true;
}

bool CCg::InitFragment(const char* szPath) {
	CMemFile file;
	byte* buffer = NULL;
	unsigned int size = 0;
	if (!CResManager::LoadTxtFile(szPath, buffer, size, file)) {
		return false;
	}

	m_nShaderID = glCreateShader(GL_FRAGMENT_SHADER);
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
		XELOG("glsl err fragment shader: %s\n%s\n", szPath, str.c_str());
		return false;
	}

	return true;
}

}

#endif //PLATFORM_OPENGLES
