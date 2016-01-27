#include "stdafx.h"
#include "XeCgProgram.h"

namespace XE {

const char* CCgProgram::s_szAttribVertex	= "Position";
const char* CCgProgram::s_szAttribTexCoord	= "TexCoord";
const char* CCgProgram::s_szAttribNormal	= "Normal";

CCgProgram::CCgProgram() : m_nProgramID(0) {
	
}

CCgProgram::~CCgProgram() {
	auto ite = m_pCgList.begin();
	auto end = m_pCgList.end();
	for (; end!=ite; ++ite) {
		glDetachShader(m_nProgramID, (*ite)->GetShaderID());
	}
	if (0 != m_nProgramID) {
		glDeleteProgram(m_nProgramID);
	}

	Reset();
}

void CCgProgram::Bind(IRenderEnv* pEnv) {
	if (0 != m_nProgramID && NULL != pEnv) {
		glUseProgram(m_nProgramID);
		auto ite = m_pCgList.begin();
		auto end = m_pCgList.end();
		for (; end!=ite; ++ite) {
			(*ite)->Bind(pEnv);
		}
	}
}

void CCgProgram::UnBind() {

}

void CCgProgram::SetTarget(IRenderTarget* pTarget) {
	if (0 != m_nProgramID && NULL != pTarget) {
		glUseProgram(m_nProgramID);
		auto ite = m_pCgList.begin();
		auto end = m_pCgList.end();
		for (; end!=ite; ++ite) {
			(*ite)->SetTarget(pTarget);
		}
	}
}
	
void CCgProgram::SetPass(CPass* pPass) {
	if (0 != m_nProgramID && NULL != pPass) {
		glUseProgram(m_nProgramID);
		auto ite = m_pCgList.begin();
		auto end = m_pCgList.end();
		for (; end!=ite; ++ite) {
			(*ite)->SetPass(pPass);
		}
	}
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
		glAttachShader(m_nProgramID, (*ite)->GetShaderID());
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
		XELOG("glsl err program: %s", str.c_str());
		return false;
	}

    ite = m_pCgList.begin();
    end = m_pCgList.end();
	for (; end!=ite; ++ite) {
	    (*ite)->OnComplete(m_nProgramID);
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

void CCgProgram::AddCg(CCg* pCg) {
	m_pCgList.XEPUSH(pCg);
}

void CCgProgram::ClearCg() {
    auto ite = m_pCgList.begin();
    auto end = m_pCgList.end();
    for (; end!=ite; ++ite) {
        XEDELETE(*ite);
    }
    m_pCgList.clear();
}
    
}
