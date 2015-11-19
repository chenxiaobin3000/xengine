#pragma once

#include "XePool.h"
#include "XeCgParam.h"

#ifdef PLATFORM_OPENGLES

namespace XE {

class CGlesCgParam :
	public CCgParam
,	public CPool<CGlesCgParam, 1024>
{
public:
	CGlesCgParam();
	virtual ~CGlesCgParam();

	bool InitParamID(GLuint nProgramID);

	virtual bool SetParam(CPass* pPass);

private:
	GLint						m_nParamID;
};

}

#endif //PLATFORM_OPENGLES
