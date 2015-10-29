/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XEIRENDERTARGET_H_
#define _XEIRENDERTARGET_H_

namespace XE {

class IRenderTarget
{
public:
	virtual ~IRenderTarget() {}

	virtual void Begin() = 0;
	virtual void End() = 0;
	virtual void Render() = 0;
};

}

#endif //_XEIRENDERTARGET_H_
