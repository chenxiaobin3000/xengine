#include "stdafx.h"
#include "XeTexture.h"
#include "XeImage.h"

namespace XE {

CTexture::CTexture() : m_nTextureID(0), m_nWidth(0), m_nHeight(0) {

}

CTexture::~CTexture() {
	if (0 != m_nTextureID) {
		glDeleteTextures(1, &m_nTextureID);
	}
}

bool CTexture::Create(byte* rgb, int width, int height, EPixelFormat format) {
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

bool CTexture::Load(const char* path) {
	if (0 != m_nTextureID) {
		return false;
	}

	// 加载文件
	CImage image;
	if (!image.Load(path)) {
		return false;
	}

	byte* rgb	= image.GetBits();
	m_nWidth	= image.GetWidth();
	m_nHeight	= image.GetHeight();

	glGenTextures(1, &m_nTextureID);
	glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgb);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return true;
}

void CTexture::Save(const char* path) {

}

void CTexture::Destroy() {
	
}

void* CTexture::Lock() {
	return NULL;
}

void CTexture::UnLock() {
	
}

void CTexture::Bind() {
	if (0 != m_nTextureID) {
		glBindTexture(GL_TEXTURE_2D, m_nTextureID);
	}
}

void CTexture::UnBind() {

}

int CTexture::GetWidth() {
	return m_nWidth;
}

int CTexture::GetHeight() {
	return m_nHeight;
}

EPixelFormat CTexture::GetFormat() {
	return EPixelFormatUnknow;
}
	
void CTexture::SetTexture(GLuint id) {
	m_nTextureID = id;
}

GLuint CTexture::GetTexture() {
	return m_nTextureID;
}

}
