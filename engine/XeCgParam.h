/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-20
 */

#ifndef _XECGPARAM_H_
#define _XECGPARAM_H_

#include "XeIRenderObject.h"

namespace XE {

enum ECgParamType {
	E_ModelViewProj,			// 变换矩阵
	E_LightMatrix,				// 光照矩阵
	E_EyePosition,				// 摄像机位置
	E_AmbiColor,				// 环境光
	E_LightColor,				// 光源颜色
	E_LightPosition,			// 光源位置
	E_MaterialD,				// 漫反射
	E_MaterialA,				// 环境反射
	E_MaterialS,				// 镜面反射
	E_MaterialE,				// 自发光
	E_FogColor,					// 雾颜色
	E_Samp0,					// 第一层纹理采样器
	E_SampDepth,				// 深度纹理采样器
	E_ParamNum					// 参数类型数
};
	
class CCgParam
{
public:
	CCgParam();
	virtual ~CCgParam();

	bool SetParam(GLuint nProgramID, IRenderObject* pObject);

private:
	GLint						m_nParamID;
	ECgParamType				m_eSetType;
};

}

#endif //_XECGPARAM_H_
