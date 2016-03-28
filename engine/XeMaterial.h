/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEMATERIAL_H_
#define _XEMATERIAL_H_

#include "XeTechnique.h"
#include "XeTechniqueManager.h"

namespace XE {

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	CTechnique* GetTechnique(ETechniqueType type);

private:
	CTechnique*					m_pTechniqueList[E_TechniqueMax];
};

}

#endif //_XEMATERIAL_H_
