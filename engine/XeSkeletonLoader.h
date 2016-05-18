/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-25
 */

#ifndef _XESKELETONLOADER_H_
#define _XESKELETONLOADER_H_

#include "XeSkeleton.h"
#include "XeAction.h"

namespace XE {

class CSkeletonLoader
{
public:
	CSkeletonLoader();
	virtual ~CSkeletonLoader();

	static CSkeleton* Load(const char* szName);

private:
	static bool LoadXml(const char* szPath);

    static bool LoadSkeleton(tinyxml2::XMLElement* pRoot, CSkeleton* pSkeleton);

    static bool LoadActions(tinyxml2::XMLElement* pActions, CSkeleton* pSkeleton);

	static const char* LoadAction(tinyxml2::XMLElement* pXml, CSkeleton* pSkeleton, CAction* pAction);
};

}

#endif //_XESKELETONLOADER_H_
