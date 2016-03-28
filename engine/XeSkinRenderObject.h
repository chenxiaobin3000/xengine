/**
 * desc: 带蒙皮的渲染节点，骨骼动画
 * auth: chenxiaobin
 * data: 2016-03-25
 */

#ifndef _XESKINRENDEROBJECT_H_
#define _XESKINRENDEROBJECT_H_

#include "XeRenderObject.h"
#include "XeSkinAssign.h"

namespace XE {

class CSkinRenderObject : public CRenderObject
{
public:
	CSkinRenderObject();
	virtual ~CSkinRenderObject();

private:
	CSkinAssignList				m_pSkinAssignList;		// 蒙皮信息
	CMatrix*					m_pMatrixList;			// 骨骼变换阵
};

}

#endif //_XESKINRENDEROBJECT_H_
