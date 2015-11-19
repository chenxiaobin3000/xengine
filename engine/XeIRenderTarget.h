/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEIRENDERTARGET_H_
#define _XEIRENDERTARGET_H_

#include "XeICamera.h"

namespace XE {

// 基础渲染元素
class IRenderTarget
{
public:
	virtual ~IRenderTarget() {}

	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Render(ICamera* pCamera) = 0;

	virtual void SetVisible(bool b) = 0;
	virtual bool IsVisible() = 0;
	virtual void SetVisibleForShadow(bool b) = 0;
	virtual bool IsVisibleForShadow() = 0;
};

}

#endif //_XEIRENDERTARGET_H_
