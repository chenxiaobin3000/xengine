/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEPASS_H_
#define _XEPASS_H_

#include "XeCgProgram.h"
#include "XeTexture.h"
#include "XeMatrix.h"
#include "XeColor.h"

namespace XE {
	
class CPass
{
public:
	CPass();
	virtual ~CPass();

	CCgProgram* GetCgProgram();

	CTexture* GetTexture();
	
	CColorF& GetMaterialDiffuse();
	
	CColorF& GetMaterialAmbient();
	
	CColorF& GetMaterialSpecular();
	
	CColorF& GetMaterialEmissive();

private:
	CCgProgram*					m_pCgProgram;
	CTexture*					m_pTexture;
	CColorF						m_MaterialDiffuse;
	CColorF						m_MaterialAmbient;
	CColorF						m_MaterialSpecular;
	CColorF						m_MaterialEmissive;
};

}

#endif //_XEPASS_H_
