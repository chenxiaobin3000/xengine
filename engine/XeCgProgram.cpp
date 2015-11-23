#include "stdafx.h"
#include "XeCgProgram.h"

namespace XE {

const char* CCgProgram::s_szAttribVertex	= "Position";
const char* CCgProgram::s_szAttribTexCoord	= "Texcoord";
const char* CCgProgram::s_szAttribNormal	= "Normal";

CCgProgram::CCgProgram() : m_nProgramID(0) {
	
}

CCgProgram::~CCgProgram() {
	auto ite = m_pCgList.begin();
	auto end = m_pCgList.end();
	for (; end!=ite; ++ite) {
		glDetachShader(m_nProgramID, ((CCg*)*ite)->m_nShaderID);
	}
	if (0 != m_nProgramID) {
		glDeleteProgram(m_nProgramID);
	}

	Reset();
}

void CCgProgram::Bind(CPass* pPass) {
	if (0 != m_nProgramID) {
		glUseProgram(m_nProgramID);
		auto ite = m_pCgList.begin();
		auto end = m_pCgList.end();
		for (; end!=ite; ++ite) {
			(*ite)->Bind(pPass);
		}
	}
}

void CCgProgram::UnBind() {

}

bool CCgProgram::Compile() {
	if (m_pCgList.empty()) {
		return true;
	}

	m_nProgramID = glCreateProgram();

	// attach vertex shader to program
	auto ite = m_pCgList.begin();
	auto end = m_pCgList.end();
	for (; end!=ite; ++ite) {
		glAttachShader(m_nProgramID, ((CGlesCg*)*ite)->m_nShaderID);
	}

	// bind attribute locations
	glBindAttribLocation(m_nProgramID, E_ATTRIB_VERTEX, s_szAttribVertex);
	glBindAttribLocation(m_nProgramID, E_ATTRIB_TEXCOORD, s_szAttribTexCoord);
	glBindAttribLocation(m_nProgramID, E_ATTRIB_NORMAL, s_szAttribNormal);

	GLint bLink;
	glLinkProgram(m_nProgramID);
	glGetProgramiv(m_nProgramID, GL_LINK_STATUS, &bLink);
	if (!bLink) {
		GLint maxLength = 0;
		glGetProgramiv(m_nProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_nProgramID, maxLength, &maxLength, &infoLog[0]);

		std::string str(infoLog.begin(), infoLog.end());
		XELOG("glsl err program: %s\n", str.c_str());
		return false;
	}

	ite = m_pCgList.begin();
	for (; end!=ite; ++ite) {
		((CGlesCg*)*ite)->InitParam(m_nProgramID);
	}

	return true;
}

bool CCgProgram::Reset() {
	auto ite = m_pCgList.begin();
	auto end = m_pCgList.end();
	for (; end!=ite; ++ite) {
		(*ite)->Reset();
	}

	ClearCg();
	return true;
}

}
