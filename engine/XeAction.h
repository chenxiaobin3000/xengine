/**
 * desc: 单个骨骼动作
 * auth: chenxiaobin
 * data: 2016-03-25
 */

#ifndef _XEACTION_H_
#define _XEACTION_H_

#include "XeVertex.h"
#include "XeQuater.h"

namespace XE {

class CAction
{
public:
	// 关键帧
	class CKeyFrame
	{
	public:
		CKeyFrame();

	public:
		int						m_nTime;
		CVertex					m_Pos;
		CQuater					m_Rot;
	};

	typedef std::vector<CKeyFrame*>						CKeyList;
	typedef std::map<int, CKeyList>						TrackMap;			// 骨骼id－关键帧集
	typedef TrackMap::value_type						TrackMapValue;

public:
	CAction();
	virtual ~CAction();

    void Init(int nTime);

    void Insert(int nID, CAction::CKeyList& List);
    
	bool GetKeyFrame(int nBoneID, int nFrame, CKeyFrame*& pCurrent, CKeyFrame*& pNext);

	int GetTime();

private:
	int							m_nTime;
	TrackMap					m_Track;
};

}

#endif //_XEACTION_H_
