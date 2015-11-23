
/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-19
 */

#ifndef _XECG_H_
#define _XECG_H_

#include "XeCgParam.h"

namespace XE {

class CCg
{
	friend class CCgParam;
	friend class CCgProgram;

public:
	enum ECgType {
		E_CgVertex,
		E_CgFragment
	};
	
public:
	CCg();
	virtual ~CCg();

	virtual bool Read(ECgType eType, const char* szPath, const char* szMain);

	virtual void Reset();

	virtual void Bind(CPass* pPass);

	virtual void UnBind();

	virtual void AddParam(CCgParam* p);

	void InitParam(GLuint nProgramID);

private:
	bool InitVertex(const char* szPath);

	bool InitFragment(const char* szPath);

private:
	GLuint						m_nShaderID;
	CCgParamList				m_CgParamList;
};

}

#endif //_XECG_H_
