/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XETECHNIQUE_H_
#define _XETECHNIQUE_H_

#include "XeCgProgram.h"
#include "XePass.h"

namespace XE {

class CTechnique
{
public:
	CTechnique();
	virtual ~CTechnique();

	void Bind(IRenderEnv* pEnv);

	void UnBind();

    void SetTarget(IRenderTarget* pTarget);
    
    void SetPass(CPass* pPass);
    
    CPass* GetPass();
    
private:
	CCgProgram*					m_pProgram;
	CPass*						m_pPass;				// 目前只支持单pass
};

}

#endif //_XETECHNIQUE_H_
