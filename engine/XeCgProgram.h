/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-20
 */

#ifndef _XECGPROGRAM_H_
#define _XECGPROGRAM_H_

#include "XeCg.h"

namespace XE {

class CCgProgram
{
public:
	enum EAttribID {
		E_ATTRIB_VERTEX,
		E_ATTRIB_TEXCOORD,
		E_ATTRIB_NORMAL,
	};

public:
	CCgProgram();
	virtual ~CCgProgram();

	virtual void Bind(CPass* pPass);

	virtual void UnBind();

	virtual bool Compile();

	virtual bool Reset();

private:
	static const char*			s_szAttribVertex;
	static const char*			s_szAttribTexCoord;
	static const char*			s_szAttribNormal;

	GLuint						m_nProgramID;
};

}

#endif //_XECGPROGRAM_H_
