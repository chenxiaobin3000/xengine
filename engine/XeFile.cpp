#include "stdafx.h"
#include "XeFile.h"

namespace XE {

CFile::CFile() : m_fp(NULL) {

}

CFile::~CFile() {
	Close();
}

bool CFile::IsExist(const char* name) {
	CFile file;
	if (file.Open(name, E_Read)) {
		file.Close();
		return true;
	}
	return false;
}

bool CFile::ReadBinary(const char* name, byte*& buffer, unsigned int& size) {
	CFile file;
	if (!CFile::IsExist(name)) {
		return false;
	}

	if (!file.Open(name, IFile::E_Read)) {
		return false;
	}

	size = file.Size();
   	buffer = NEW_LOG(byte[m_nSize]);
	if (!buffer) {
		size = 0;
		file.Close();
		return false;
	}

	if (!file.Read(buffer, size)) {
		file.Close();
		return false;
	}

	file.Close();
	return true;
}

bool CFile::ReadText(const char* name, byte*& buffer, unsigned int& size) {
	CFile file;
	if (!CFile::IsExist(name)) {
		return false;
	}

	if (!file.Open(name, IFile::E_Read)) {
		return false;
	}

	size = file.Size() + 1;
	buffer = NEW_LOG(byte[m_nSize]);
	if (!buffer) {
		size = 0;
		file.Close();
		return false;
	}

	buffer[size-1] = 0;
	if (!file.Read(buffer, size-1)) {
		file.Close();
		return false;
	}

	file.Close();
	return true;
}

bool CFile::Open(const char* name, EFileMode mode) {
	int len = strlen(name);
	if ('\\' == name[len-1] || '/' == name[len-1]) {
		return false;
	}

	if (m_fp) {
		return false;
	}
	switch (mode) {
	case E_Read:
		m_fp = fopen(name, "rb");
		break;

	case E_Write:
		m_fp = fopen(name, "wb");
		break;

	default:
		break;
	}
	if (!m_fp) {
		return false;
	}
	return true;
}

void CFile::Close() {
	if (m_fp) {
		fclose(m_fp);
		m_fp = NULL;
	}
}

bool CFile::Read(byte* buffer, unsigned int size) {
	if (size != (int)fread(buffer, 1, size, m_fp)) {
		return false;
	}
	return true;
}

bool CFile::Write(const byte* buffer, unsigned int size) {
	if (size != fwrite(buffer, 1, size, m_fp)) {
		return false;
	}
	return true;
}

unsigned int CFile::Size() {
	int length = 0;
	if (m_fp) {
		int offset = ftell(m_fp);
		fseek(m_fp, 0, SEEK_END);
		length = ftell(m_fp);
		fseek(m_fp, offset, SEEK_SET);
	}
	return length;
}

}
