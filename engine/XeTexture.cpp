#include "stdafx.h"
#include "XeTexture.h"

namespace XE {

CTexture::CTexture() : m_nTextureID(0), m_nWidth(0), m_nHeight(0) {

}

CTexture::~CTexture() {
	if (0 != m_nTextureID) {
		glDeleteTextures(1, &m_nTextureID);
	}
}

void CTexture::Bind(int id) {
	if (0 != m_nTextureID) {
		glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	}
}

void CTexture::UnBind(int id) {

}
/*
bool CTexture::LoadRGB(byte* rgb, int width, int height) {
	if (0 != m_nTextureID) {
		return false;
	}

	m_nWidth = width;
	m_nHeight = height;
	glGenTextures(1, &m_nTextureID);
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgb);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return true;
}

bool CTexture::Deserialize(const char* path, const char* szLocalPath) {
	if (0 != m_nTextureID) {
		return false;
	}

	// ╪стьнд╪Ч
	CImage image;
	if (!image.Deserialize(path, path)) {
		return false;
	}

	byte* rgb	= image.GetBits();
	int width	= image.GetWidth();
	int height	= image.GetHeight();
	m_nWidth	= width;
	m_nHeight	= height;

	glGenTextures(1, &m_nTextureID);
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgb);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return true;
}

void CTexture::Save(const char* path) {

}

void CTexture::SetTexture(GLuint id) {
	m_nTextureID = id;
}

GLuint CTexture::GetTexture() {
	return m_nTextureID;
}
*/
}
