/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-30
 */

#ifndef _XEXFILE_H_
#define _XEXFILE_H_

#include "XeFile.h"

namespace XE {

class CXFile :
	public CFile
{
public:
	CXFile();
	virtual ~CXFile();

	static bool IsExist(const char* name);

	static bool ReadFile(const char* name, byte*& buffer, unsigned int& size);

	static bool ReadText(const char* name, byte*& buffer, unsigned int& size);
	
	static const char* GetWritablePath();

private:
	static std::string			s_strTmp;
};		

}

#endif //_XEXFILE_H_
