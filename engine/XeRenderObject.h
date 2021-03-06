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
#include "XeQuater.h"
#include "XeAABB.h"
#include "XeVertexBuffer.h"

namespace XE {

// 公告板类型
enum EBillBoardType {
	EBBT_Cylindrical,		// 圆柱
	EBBT_Spherical			// 球形
};

class CRenderObject : public IRenderTarget
{
public:
	CRenderObject();
	virtual ~CRenderObject();

	virtual void Render(CCamera* camera);
	virtual void Draw();

	virtual void SetVisible(bool b);
	virtual bool IsVisible();
	virtual void SetVisibleForShadow(bool b);
	virtual bool IsVisibleForShadow();

	virtual CMatrix& GetModelViewProj();
    virtual void SetMaterial(CMaterial* pMaterial);
    virtual CMaterial* GetMaterial();
    virtual void SetTexture(CTexture* pTexture);
    virtual CTexture* GetTexture();

	void SetVertexBuffer(CVertexBuffer* pVertexBuffer);
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

protected:
	virtual void GenerateAABB();
	
	// 坐标变换
	void _World2Screen(CVertex& ScreenVertex, CVertex& WorldVertex, 
					   float width, float height, CMatrix& CameraMatrix);

	void _Screen2World(CVertex& WorldVertex, CVertex& ScreenVertex, 
		float width, float height, CMatrix& CameraMatrix);
	
public:
	static const CVertex		s_DefaultForward;
	static const CVertex		s_DefaultBack;
	static const CVertex		s_DefaultLeft;
	static const CVertex		s_DefaultRight;
	static const CVertex		s_DefaultUp;
	static const CVertex		s_DefaultDown;

protected:
	bool						m_bVisible;				// 可视
	bool						m_bVisibleForShadow;	// 是否生成影子

	CMatrix						m_ModelViewProj;		// 世界矩阵(临时)
    CVertexBuffer*				m_pVertexBuffer;		// 顶点
	CMaterial*					m_pMaterial;			// 材质
    CTexture*                   m_pTexture;             // 纹理

	CVertex						m_LocalForward;			// 前方向(本地坐标)
	CVertex						m_LocalUp;				// 上方向(本地坐标)
	CVertex						m_Forward;				// 前方向
	CVertex						m_Position;				// 当前坐标
	CQuater						m_Rotation;				// 旋转
	CMatrix						m_Matrix;				// 变换矩阵

	CAABB						m_AABB;					// 包围盒
};

}

#endif //_XERENDEROBJECT_H_
