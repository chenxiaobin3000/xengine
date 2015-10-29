/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEBEZIER_H_
#define _XEBEZIER_H_

#include "XePool.h"
#include "XeVertex.h"

namespace XE {

class CBezier3 :
	public CPool<CBezier3, 32>
{
public:
	enum EPower {
		E_Power2 = 2,			// 二次方
		E_Power3,				// 三次方
		E_PowerMax
	};

public:
	CBezier3(EPower p);
	virtual ~CBezier3();

	void SetPoint(const CVertex& v, int index);

	CVertex& GetValue(float t);

	void GetValue(CVertexList& list);

private:
	static const int s_nBezierNum = E_PowerMax;

private:
	EPower				m_ePower;
	CVertex				m_v[s_nBezierNum];
	CVertex				m_Result;
};

}

#endif //_XEBEZIER_H_
