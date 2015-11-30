/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-19
 */

#ifndef _XECG_H_
#define _XECG_H_

#include "XeCgProgramListener.h"
#include "XeCgParam.h"

namespace XE {

class CCg :
	public CCgProgramListener
{
public:
	enum ECgType {
		E_CgVertex,
		E_CgFragment
	};
	
public:
	CCg();
	virtual ~CCg();

	virtual void OnComplete(GLuint nProgramID);
		
	bool Read(ECgType eType, const char* szPath);

	void Reset();

	void Bind(IRenderEnv* pEnv);

	void UnBind();

	void SetTarget(IRenderTarget* pTarget);
	
	void AddParam(CCgParam* p);

	GLuint GetShaderID();

private:
	bool Init(GLenum type, const char* szPath);

private:
	GLuint						m_nShaderID;
	std::vector<CCgParam*>		m_EnvParamList;
	std::vector<CCgParam*>		m_TargetParamList;
};

}

#endif //_XECG_H_
