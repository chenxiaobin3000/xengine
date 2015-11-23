/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-20
 */

#ifndef _XERENDEROBJECT_H_
#define _XERENDEROBJECT_H_

#include "XeIRenderObject.h"

namespace XE {

class CRenderObject : public IRenderObject
{
public:
	CRenderObject();
	virtual ~IRenderTarget();

	virtual void Begin();
	virtual void End();
	virtual void Render(ICamera* pCamera);

	virtual void SetVisible(bool b);
	virtual bool IsVisible();
	virtual void SetVisibleForShadow(bool b);
	virtual bool IsVisibleForShadow();
};

}

#endif //_XERENDEROBJECT_H_
