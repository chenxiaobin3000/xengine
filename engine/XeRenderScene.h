/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-10
 */

#ifndef _XERENDERSCENE_H_
#define _XERENDERSCENE_H_

#include "XeIRenderTarget.h"

// 渲染情景
namespace XE {

class CRenderScene : IRenderTarget
{
public:
	CRenderScene();
	virtual ~CRenderScene();
};

}

#endif //_XERENDERSCENE_H_
