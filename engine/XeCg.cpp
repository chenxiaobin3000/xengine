#include "stdafx.h"
#include "XeGlesCg.h"
#include "XeGlesRenderSystem.h"
#include "XeResManager.h"

#ifdef PLATFORM_OPENGLES

namespace XE {

const char*		CGlesCg::s_szVertexFlag		= "_v.glsl";
const char*		CGlesCg::s_szFragmentFlag	= "_f.glsl";
const char*		CGlesCg::s_szMain			= "main";

CGlesCg::CGlesCg() : m_nShaderID(0) {

}

CGlesCg::~CGlesCg() {
	// FreeList<CCgParam>(m_CgParamList); 基类已释放

	if (0 != m_nShaderID) {
		glDeleteShader(m_nShaderID);
	}
}

bool CGlesCg::Deserialize(const char* szPath, const char* szMain) {
	if (strstr(szPath, s_szVertexFlag)) {
		m_eType = E_CgVertex;
	} else if (strstr(szPath, s_szFragmentFlag)) {
		m_eType = E_CgFragment;
	} else {
		return false;
	}

	bool bRet = false;
	switch (m_eType) {
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

void CGlesCg::Reset() {
	m_nShaderID = 0;
}

void CGlesCg::Bind(CPass* pPass) {
	auto ite = m_CgParamList.begin();
	auto end = m_CgParamList.end();
	for (; end!=ite; ++ite) {
		(*ite)->SetParam(pPass);
	}
}

void CGlesCg::UnBind() {

}

void CGlesCg::AddParam(CCgParam* p) {
	m_CgParamList.PUSH(p);
}

void CGlesCg::InitParam(GLuint nProgramID) {
	auto ite = m_CgParamList.begin();
	auto end = m_CgParamList.end();
	for (; end!=ite; ++ite) {
		((CGlesCgParam*)(*ite))->InitParamID(nProgramID);
	}
}

bool CGlesCg::InitVertex(const char* szPath) {
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

bool CGlesCg::InitFragment(const char* szPath) {
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
