/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-02-21
 */

#ifndef _XESKELETON_H_
#define _XESKELETON_H_

#include "XeBone.h"
#include "XeMatrix.h"
#include "XeAction.h"

namespace XE {

class CSkeleton
{
private:
	struct SParam {
		CAction					pAction;
		int						nFrame;
	};
	typedef std::map<std::string, CBone*>				BoneMap;
	typedef BoneMap::value_type							BoneMapValue;
	typedef std::map<int, CBone*>						BoneIDMap;
	typedef BoneIDMap::value_type						BoneIDMapValue;
	typedef std::map<std::string, CAction*>				ActionMap;
	typedef ActionMap::value_type						ActionMapValue;

public:
	CSkeleton();
	virtual ~CSkeleton();
	
	bool SetPose(const char* szAction, int nFrame);

	CMatrix* GetMatrixList() const;

	int GetBoneID(const char* szName) const;
	
private:
	// 应用轨迹
	static void ApplyTrack(CBone* pBone, void* pParam);

	// 骨骼变换
	static void BoneTransform(CBone* pBone, void* pParam);
	
private:
	CBone*						m_pRootBone;
	BoneMap						m_BoneMap;
	ActionMap					m_ActionMap;
	CMatrix*					m_pMatrixList;			// 骨骼变换阵
};

}

#endif //_XESKELETON_H_
