/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-26
 */

#ifndef _XECAMERA_H_
#define _XECAMERA_H_

#include "XeRenderObject.h"
#include "XeMatrix.h"
#include "XePoint.h"
#include "XePlane.h"

namespace XE {

// 镜头透视类型
enum ECameraPerspectiveType {
	ECPT_Perspective,		// 透视模式
	ECPT_Ortho				// 正交模式
};

class CCamera : public CRenderObject
{
public:
	CCamera(CVertex& forward, CPoint& screen, float zn, float zf);
	CCamera(float vx, float vy, float vz, float width, float height, float zn, float zf);
    virtual ~CCamera();

	virtual void Render(CCamera* camera);

	void Lookat();
	
	void SetPerspectiveType(ECameraPerspectiveType type);

	ECameraPerspectiveType GetPerspectiveType();

	float GetScreenWidth();

	float GetScreenHeight();

	float zn();

	float zf();

	CMatrix& GetRenderMatrix();
	
	// 坐标转换
	CVertex& World2Screen(CVertex& WorldVertex);

	CVertex& Screen2World(CVertex& ScreenVertex);

protected:
	// 视锥裁切函数
	virtual void GenerateViewCone(float width, float height);

	void TransformMatrix(GLfloat* pFrom, CMatrix* pTo);

public:
	static const float			s_pn;					// 投影坐标最近值
	static const float			s_pf;					// 投影坐标最远值

protected:
	ECameraPerspectiveType		m_ePerspectiveType;		// 透视类型
	float						m_fScreenWidth;			// 屏幕宽
	float						m_fScreenHeight;		// 屏幕高
	float						m_fViewNear;			// 视锥近
	float						m_fViewFar;				// 视锥远
	CMatrix						m_RenderMatrix;			// 变换矩阵

	CVertex						m_WorldVertex;			// 世界坐标（临时保存）
	CVertex						m_ScreenVertex;			// 屏幕坐标（临时保存）

	CPlane						m_NearPlane;			// 近截面
	CPlane						m_FarPlane;				// 远截面
	CPlane						m_LeftPlane;			// 左截面
	CPlane						m_RightPlane;			// 右截面
	CPlane						m_UpPlane;				// 上截面
	CPlane						m_DownPlane;			// 下截面
};

}

#endif //_XECAMERA_H_
