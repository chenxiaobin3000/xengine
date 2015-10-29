/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-29
 */

#ifndef _XERAY_H_
#define _XERAY_H_

#include "XeVertex.h"

namespace XE {

class CRay
{
public:
	CRay();

	CRay(const CRay& o);

	CRay(CVertex& ip, CVertex& id);

	virtual ~CRay();

	bool operator==(const CRay& r);

	bool operator!=(const CRay& r);

	void Set(CVertex& ip, CVertex& id);

	void Identity();

public:
	CVertex						p;
	CVertex						d;
};

}

#endif //_XERAY_H_
