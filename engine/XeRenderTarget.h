/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XERENDERTARGET_H_
#define _XERENDERTARGET_H_

namespace XE {

class IRenderTarget
{
 public:
	virtual IRenderTarget() {}

	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Render() = 0;
};

}

#endif //_XERENDERTARGET_H_