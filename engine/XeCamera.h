/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-26
 */

#ifndef _XECAMERA_H_
#define _XECAMERA_H_

#include "XeMatrix.h"
//#include "XeCameraGrid.h"

namespace XE {

class CBillBoard;

class CCamera
{
public:
/*	CCamera(float vx, float vy, float vz, float width, float height, float zn, float zf);
	virtual ~CCamera();

	virtual void Render(CSceneObject* pCamera, ERenderType eType);

	// 获取类型
	virtual ESceneObjectType GetType() {
		return E_Camera;
	}

	void SetCanLook(bool bCanLook);

	void SetPerspectiveType(ECameraPerspectiveType type);

	ECameraPerspectiveType GetPerspectiveType();

	float GetScreenWidth();

	float GetScreenHeight();

	float zn();

	float zf();

	// 坐标变换
	CVertex& World2Screen(CVertex& WorldVertex);

	CVertex& Screen2World(CVertex& ScreenVertex);

	CVertex& GetGridPosition();

	// 绑定格子策略
	bool IsAttachGrid();

	void AttachGrid(CCameraGrid* ob);

	void DetachGrid();

	PROPERTY(ShowGrid, bool, m_bShowGrid);

protected:
	virtual void GenerateAABB() {}

	// 视锥裁切函数
	virtual void GenerateViewCone(float width, float height);

public:
	static const float			s_pn;					// 投影坐标最近值
	static const float			s_pf;					// 投影坐标最远值

private:
	static const float			s_fGridDistance;		// 前方格子显示距离
	static const float			s_fCameraWidth;			// 渲染时用的代替物
	static const float			s_fCameraHeight;		// 渲染时用的代替物
	static const char*			s_szMatePath;			// 渲染时用的代替物

protected:
	ECameraPerspectiveType		m_ePerspectiveType;		// 透视类型
	float						m_fScreenWidth;			// 屏幕宽
	float						m_fScreenHeight;		// 屏幕高
	float						m_fViewNear;			// 视锥近
	float						m_fViewFar;				// 视锥远

	CVertex						m_WorldVertex;			// 世界坐标（临时保存）
	CVertex						m_ScreenVertex;			// 屏幕坐标（临时保存）
	CVertex						m_GridVertex;			// 格子坐标（临时保存）

	CPlane						m_NearPlane;			// 近截面
	CPlane						m_FarPlane;				// 远截面
	CPlane						m_LeftPlane;			// 左截面
	CPlane						m_RightPlane;			// 右截面
	CPlane						m_UpPlane;				// 上截面
	CPlane						m_DownPlane;			// 下截面

	bool						m_bShowGrid;			// 显示格子
	CCameraGrid*				m_pCameraGrid;			// 摄像机格子策略
	CVertexList					m_LineList;				// 画线

	CBillBoard*					m_pBillBoard;			// 渲染时用的代替物*/
};

}

#endif //_XECAMERA_H_
