/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEMATERIAL_H_
#define _XEMATERIAL_H_

#include "XeTechnique.h"

namespace XE {

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	void Bind(IRenderEnv* pEnv);

	void UnBind();

    void SetTarget(IRenderTarget* pTarget);
    
    void SetTechnique(CTechnique* pTechnique);
    
    CTechnique* GetTechnique();
    
private:
	CTechnique*					m_pTechnique;			// 目前只支持单技术
};

}

#endif //_XEMATERIAL_H_
