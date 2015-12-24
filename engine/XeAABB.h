/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-12-16
 */

#ifndef _XEAABB_H_
#define _XEAABB_H_

#include "XeVertex.h"
#include "XeColor.h"

namespace XE {

class CRay;
class COBB;

class CAABB
{
public:
	CAABB();

	CAABB(const CVertex& min, const CVertex& max);

	virtual ~CAABB();

	CAABB& operator=(const CAABB& o);

	void Set(CVertex& min, CVertex& max);

	// 判断相交
	bool Intersect(const CVertex& v);

	// 判断相交
	bool Intersect(const CVertex& v1, const CVertex& v2);

	// 判断相交
	bool Intersect(const CRay& r);

	// 判断相交
	bool Intersect(const CAABB& pIBB);

	// 判断相交
	bool Intersect(const COBB& pIBB);

	// 判断包含
	bool Contain(const CVertex& v);

	// 判断包含
	bool Contain(const CVertex& v1, const CVertex& v2);

	// 判断包含
	bool Contain(const CRay& r);

	// 判断包含
	bool Contain(const CAABB& pIBB);

	// 判断包含
	bool Contain(const COBB& pIBB);

	void Render(byte r, byte g, byte b);

	void SetPosition(const CVertex& v);

	void SetPosition(float x, float y, float z);

	void Move(const CVertex& v);

	void Move(float x, float y, float z);

public:
	static const float			s_fMax;					// 初始化最大值

	CVertex						m_Min;					// 最小值
	CVertex						m_Max;					// 最大值
};

#endif //_XEAABB_H_
