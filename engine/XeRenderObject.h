/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-20
 */

#ifndef _XERENDEROBJECT_H_
#define _XERENDEROBJECT_H_

#include "XeIRenderTarget.h"
#include "XeMatrix.h"
#include "XeMaterial.h"

namespace XE {

class CRenderObject : public IRenderTarget
{
public:
	CRenderObject();
	virtual ~CRenderObject();

	virtual void Begin();
	virtual void End();
	virtual void Render(IRenderEnv* pEnv);

	virtual void SetVisible(bool b);
	virtual bool IsVisible();
	virtual void SetVisibleForShadow(bool b);
	virtual bool IsVisibleForShadow();

	virtual CMatrix& GetModelViewProj();

	void SetPosition(const CVertex& v);
	void SetPosition(float x, float y, float z);
	void SetRotation(const CQuater& q);

	// 移动：x 左右，y 上下，z 前后
	void Move(const CVertex& v);
	void Move(float x, float y, float z);

	// roll 翻滚，前后为轴，pitch 俯仰，左右为轴，yaw 偏航，上下为轴
	void Roll(float fAngle);
	void Pitch(float fAngle);
	void Yaw(float fAngle);

	// 转向面对指定点
	void Turn2Face(CVertex& pos, EBillBoardType type);
	void Turn2Face(float x, float y, float z, EBillBoardType type);

	CVertex& GetLocalForward();
	CVertex& GetForward();
	CVertex& GetPosition();
	CQuater& GetRotation();
	CAABB& GetAABB();

public:
	static const CVertex		s_DefaultForward;
	static const CVertex		s_DefaultBack;
	static const CVertex		s_DefaultLeft;
	static const CVertex		s_DefaultRight;
	static const CVertex		s_DefaultUp;
	static const CVertex		s_DefaultDown;

private:
	bool						m_bVisible;				// 可视
	bool						m_bVisibleForShadow;	// 是否生成影子

	CMatrix						m_ModelViewProj;
	CMaterial*					m_pMaterial;

	CVertex						m_LocalForward;			// 前方向(本地坐标)
	CVertex						m_LocalUp;				// 上方向(本地坐标)
	CVertex						m_Forward;				// 前方向
	CVertex						m_Position;				// 当前坐标
	CQuater						m_Rotation;				// 旋转
	CMatrix						m_Matrix;				// 变换矩阵
};

}

#endif //_XERENDEROBJECT_H_
