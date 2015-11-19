#pragma once

#include "XeGlesCgParam.h"
#include "XeCg.h"

#ifdef PLATFORM_OPENGLES

namespace XE {

class CGlesCg :
	public CCg
,	public CPool<CGlesCg, 1024>
{
	friend class CGlesCgProgram;

public:
	CGlesCg();
	virtual ~CGlesCg();

	virtual bool Deserialize(const char* szPath, const char* szMain);

	virtual void Reset();

	virtual void Bind(CPass* pPass);

	virtual void UnBind();

	virtual void AddParam(CCgParam* p);

	void InitParam(GLuint nProgramID);

private:
	bool InitVertex(const char* szPath);

	bool InitFragment(const char* szPath);

public:
	static const char*			s_szVertexFlag;
	static const char*			s_szFragmentFlag;
	static const char*			s_szMain;

private:
	GLuint						m_nShaderID;
};

}

#endif //PLATFORM_OPENGLES
