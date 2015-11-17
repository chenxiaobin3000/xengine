/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEIRENDERSCENE_H_
#define _XEIRENDERSCENE_H_

#include "XeIRenderTarget.h"

// 渲染情景：ui、3d
namespace XE {

class IRenderScene : IRenderTarget
{
public:
	virtual ~IRenderScene() {}
};

}

#endif //_XEIRENDERSCENE_H_
