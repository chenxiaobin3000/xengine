/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-28
 */

#ifndef _XETECHNIQUEMANAGER_H_
#define _XETECHNIQUEMANAGER_H_

#include "XeSingleton.h"

namespace XE {

enum ETechniqueType {
	E_TechniqueNormal,
	E_TechniqueShadow,
};
	
class CTechniqueManager :
	public CSingleton<CTechniqueManager>
{
	friend class CSingleton<CTechniqueManager>;

private:
	CTechniqueManager();
	virtual ~CTechniqueManager();

public:
	bool Init();
	
	virtual void Free();

	void SetTechnique(ETechniqueType type);

	ETechniqueType GetTechnique();

private:
	ETechniqueType				m_eTechnique;
};

}

#endif //_XETECHNIQUEMANAGER_H_
