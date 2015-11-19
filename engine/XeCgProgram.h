#pragma once

#include "XeGlesCg.h"
#include "XeCgProgram.h"

#ifdef PLATFORM_OPENGLES

namespace XE {

class CGlesCgProgram :
	public CCgProgram
,	public CPool<CGlesCgProgram, 256>
{
public:
	enum EAttribID {
		E_ATTRIB_VERTEX,
		E_ATTRIB_TEXCOORD,
		E_ATTRIB_NORMAL,
		E_ATTRIB_COLOR,
	};

public:
	CGlesCgProgram();
	virtual ~CGlesCgProgram();

	virtual void Bind(CPass* pPass);

	virtual void UnBind();

	virtual bool Compile();

	virtual bool Reset();

private:
	static const char*			s_szAttribVertex;
	static const char*			s_szAttribTexCoord;
	static const char*			s_szAttribNormal;
	static const char*			s_szAttribColor;

	GLuint						m_nProgramID;
};

}

#endif //PLATFORM_OPENGLES
