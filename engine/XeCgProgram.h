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

	void Bind(IRenderEnv* pEnv);

	void UnBind();

	void SetTarget(IRenderTarget* pTarget);
	
	void SetPass(CPass* pPass);
	
	bool Compile();

	bool Reset();

	void AddCg(CCg* pCg);

    void ClearCg();
    
private:
	static const char*			s_szAttribVertex;
	static const char*			s_szAttribTexCoord;
	static const char*			s_szAttribNormal;

	GLuint						m_nProgramID;
    std::vector<CCg*>           m_pCgList;
};

}

#endif //_XECGPROGRAM_H_
