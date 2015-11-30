/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XETECHNIQUE_H_
#define _XETECHNIQUE_H_

#include "XePass.h"

namespace XE {

class CTechnique
{
public:
	CTechnique();
	virtual ~CTechnique();

	std::vector<CPass*>& GetPassList();

private:
	std::vector<CPass*>			m_pPassList;
};

}

#endif //_XETECHNIQUE_H_
