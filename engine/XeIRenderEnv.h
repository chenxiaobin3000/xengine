/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-21
 */

#ifndef _XEIRENDERENV_H_
#define _XEIRENDERENV_H_

#include "XeIRenderTarget.h"

namespace XE {

class CTexture;
class CVertex;
class CColorF;

class IRenderEnv : public IRenderTarget
{
public:
	virtual ~IRenderEnv() {}

	virtual CTexture* GetDepthTexture() = 0;

	virtual CMatrix& GetCameraMatrix() = 0;
	
	virtual CMatrix& GetLightMatrix() = 0;

	virtual CVertex& GetEyePosition() = 0;

	virtual CColorF& GetAmbientColor() = 0;

	virtual CColorF& GetLightColor() = 0;

	virtual CVertex& GetLightPosition() = 0;
};

}

#endif //_XEIRENDERENV_H_
