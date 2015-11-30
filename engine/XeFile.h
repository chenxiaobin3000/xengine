/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-20
 */

#ifndef _XEFILE_H_
#define _XEFILE_H_

#include "XeIFile.h"

namespace XE {

class CFile : 
	public IFile
{
public:
	CFile();
	virtual ~CFile();

	static bool IsExist(const char* name);

	static bool ReadFile(const char* name, byte*& buffer, unsigned int& size);

	static bool ReadText(const char* name, byte*& buffer, unsigned int& size);
	
	virtual bool Open(const char* name, IFile::EFileMode mode);

	virtual void Close();

	virtual bool Read(byte* buffer, unsigned int size);

	virtual bool Write(const byte* buffer, unsigned int size);

	virtual unsigned int Size();

private:
	FILE*						m_fp;
};

}

#endif //_XEFILE_H_
