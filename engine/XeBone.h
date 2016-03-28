/**
 * desc: 骨头数据，不涉及资源导入
 * auth: chenxiaobin
 * data: 2016-02-22
 */

#ifndef _XEBONE_H_
#define _XEBONE_H_

#include "XeQuater.h"

namespace XE {

class CBone
{
public:
	typedef void (*ForEachBoneCallback)(CBone* pBone, void* pParam);

public:
	struct SBoneInfo {
		CVertex		pos;		// 位移
		CQuater		rot;		// 旋转
	};

public:
	CBone();
	CBone(const CBone& b);
	virtual ~CBone();

	CBone& operator=(const CBone& o);

	// 获取骨骼数
	int GetSize();

	// 重置骨骼
	void Reset();

	// 对骨骼做衍生，获取父节点变换
	void Derived();

	// 生成实际绑定
	void BindPose();

	// 遍历函数，自顶向下，优先处理当前节点
	static void ForEachBoneForward(CBone* pNode, void* pParam, ForEachBoneCallback pFunc);

	// 遍历函数，自顶向下，最后处理当前节点
	static void ForEachBoneBack(CBone* pNode, void* pParam, ForEachBoneCallback pFunc);

	// 释放骨骼链
	static void FreeList(CBone* pNode);

public:
	int							m_nID;					// id
	CBone*						m_pParent;				// 父节点
	CBone*						m_pNext;				// 同级节点
	CBone*						m_pChild;				// 子节点

	SBoneInfo					m_Pose;					// 当前值
	SBoneInfo					m_Init;					// 初始值
	SBoneInfo					m_Derived;				// 继承值
	SBoneInfo					m_InverseDerived;		// 逆继承值
};

}

#endif //_XEBONE_H_
