/**
 * desc: 蒙皮信息
 * auth: chenxiaobin
 * data: 2016-03-28
 */

#ifndef _XESKINASSIGN_H_
#define _XESKINASSIGN_H_

namespace XE {

class CSkinAssign
{
public:
	// 蒙皮点
	class CSkinPoint
	{
	public:
		CSkinPoint(int id, float w);
		virtual ~CSkinPoint();

	public:
		int		m_nBoneIdx;
		float	m_fWeight;
	};

public:
	typedef std::vector<CSkinPoint>						SAList;
	typedef std::map<int, SAList>						SAMap;			// 点id - 点信息
	typedef SAMap::value_type							SAMapValue;

public:
	CSkinAssign();
	virtual ~CSkinAssign();

	void Insert(int nVertexIdx, int nBoneIdx, float fWeight);

	bool Empty();

public:
	SAMap	m_Map;
};

typedef std::vector<CSkinAssign*>					CSkinAssignList;

}

#endif //_XESKINASSIGN_H_
