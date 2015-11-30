/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-19
 */

#ifndef _XEIFILE_H_
#define _XEIFILE_H_

namespace XE {

class IFile
{
public:
	enum EFileMode {
		E_Read,
		E_Write
	};

public:
	virtual ~IFile() {}
	virtual bool Open(const char* name, EFileMode mode) = 0;
	virtual void Close() = 0;
	virtual bool Read(byte* buffer, unsigned int size) = 0;
	virtual bool Write(const byte* buffer, unsigned int size) = 0;
	virtual unsigned int Size() = 0;
};

}

#endif //_XEIFILE_H_
