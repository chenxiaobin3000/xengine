/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-21
 */

#ifndef _XEIRENDEROBJECT_H_
#define _XEIRENDEROBJECT_H_

#include "XeIRenderTarget.h"

namespace XE {

class IRenderObject : public IRenderTarget
{
public:
	virtual ~IRenderObject() {}

//	virtual GetLight() = 0;
};

}

#endif //_XEIRENDEROBJECT_H_
