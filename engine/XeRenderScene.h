/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-10
 */

#ifndef _XERENDERSCENEUI_H_
#define _XERENDERSCENEUI_H_

#include "XeIRenderTarget.h"

// 3d渲染情景
namespace XE {

class CRenderScene3D : IRenderTarget
{
public:
	CRenderScene3D();
	virtual ~CRenderScene3D();
};

}

#endif //_XERENDERSCENEUI_H_
