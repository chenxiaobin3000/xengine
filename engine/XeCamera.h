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

	// ��ȡ����
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

	// ����任
	CVertex& World2Screen(CVertex& WorldVertex);

	CVertex& Screen2World(CVertex& ScreenVertex);

	CVertex& GetGridPosition();

	// �󶨸��Ӳ���
	bool IsAttachGrid();

	void AttachGrid(CCameraGrid* ob);

	void DetachGrid();

	PROPERTY(ShowGrid, bool, m_bShowGrid);

protected:
	virtual void GenerateAABB() {}

	// ��׶���к���
	virtual void GenerateViewCone(float width, float height);

public:
	static const float			s_pn;					// ͶӰ�������ֵ
	static const float			s_pf;					// ͶӰ������Զֵ

private:
	static const float			s_fGridDistance;		// ǰ��������ʾ����
	static const float			s_fCameraWidth;			// ��Ⱦʱ�õĴ�����
	static const float			s_fCameraHeight;		// ��Ⱦʱ�õĴ�����
	static const char*			s_szMatePath;			// ��Ⱦʱ�õĴ�����

protected:
	ECameraPerspectiveType		m_ePerspectiveType;		// ͸������
	float						m_fScreenWidth;			// ��Ļ��
	float						m_fScreenHeight;		// ��Ļ��
	float						m_fViewNear;			// ��׶��
	float						m_fViewFar;				// ��׶Զ

	CVertex						m_WorldVertex;			// �������꣨��ʱ���棩
	CVertex						m_ScreenVertex;			// ��Ļ���꣨��ʱ���棩
	CVertex						m_GridVertex;			// �������꣨��ʱ���棩

	CPlane						m_NearPlane;			// ������
	CPlane						m_FarPlane;				// Զ����
	CPlane						m_LeftPlane;			// �����
	CPlane						m_RightPlane;			// �ҽ���
	CPlane						m_UpPlane;				// �Ͻ���
	CPlane						m_DownPlane;			// �½���

	bool						m_bShowGrid;			// ��ʾ����
	CCameraGrid*				m_pCameraGrid;			// ��������Ӳ���
	CVertexList					m_LineList;				// ����

	CBillBoard*					m_pBillBoard;			// ��Ⱦʱ�õĴ�����*/
};

}

#endif //_XECAMERA_H_
