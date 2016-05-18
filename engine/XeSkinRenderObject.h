/**
 * desc: 带蒙皮的渲染节点，骨骼动画
 * auth: chenxiaobin
 * data: 2016-03-25
 */

#ifndef _XESKINRENDEROBJECT_H_
#define _XESKINRENDEROBJECT_H_

#include "XeRenderObject.h"
#include "XeSkeleton.h"
#include "XeSkinAssign.h"

namespace XE {

class CSkinRenderObject : public CRenderObject
{
public:
	CSkinRenderObject();
	virtual ~CSkinRenderObject();

    void SetSkeleton(CSkeleton* pSkeleton);

    CSkinAssign& GetSkinAssign();
    
private:
    CSkeleton*					m_pSkeleton;			// 骨骼信息
	CSkinAssign					m_SkinAssign;			// 蒙皮信息
	CMatrix*					m_pMatrixList;			// 骨骼变换阵
};

}

#endif //_XESKINRENDEROBJECT_H_
