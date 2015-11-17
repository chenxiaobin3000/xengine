/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-17
 */

#ifndef _XEICAMERA_H_
#define _XEICAMERA_H_

namespace XE {

class ICamera
{
public:
	virtual ~ICamera() {}

	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	virtual float getLeft() = 0;
	virtual float getTop() = 0;
	virtual float getRight() = 0;
	virtual float getBottom() = 0;
	virtual float getNear() = 0;
	virtual float getFar() = 0;
};

}

#endif //_XEICAMERA_H_
