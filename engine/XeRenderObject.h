/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-20
 */

#ifndef _XERENDEROBJECT_H_
#define _XERENDEROBJECT_H_

#include "XeIRenderTarget.h"
#include "XeMatrix.h"
#include "XeMaterial.h"

namespace XE {

class CRenderObject : public IRenderTarget
{
public:
	CRenderObject();
	virtual ~CRenderObject();

	virtual void Begin();
	virtual void End();
	virtual void Render(IRenderEnv* pEnv);

	virtual void SetVisible(bool b);
	virtual bool IsVisible();
	virtual void SetVisibleForShadow(bool b);
	virtual bool IsVisibleForShadow();

	virtual CMatrix& GetModelViewProj();

private:
	bool						m_bVisible;
	bool						m_bVisibleForShadow;

	CMatrix						m_ModelViewProj;
	CMaterial*					m_pMaterial;
};

}

#endif //_XERENDEROBJECT_H_
