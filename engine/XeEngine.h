/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-21
 */

#ifndef _XEENGINE_H_
#define _XEENGINE_H_

#include "XeSingleton.h"

namespace XE {

class CEngine :
   	public CSingleton<CEngine>
{
	friend class CSingleton<CEngine>;
	
private:
	CEngine();
	virtual ~CEngine();

public:
	bool Init();

	virtual void Free();

	bool Reset();

	bool Render();
};

}

#endif //_XEENGINE_H_
