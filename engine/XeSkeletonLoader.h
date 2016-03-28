/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-25
 */

#ifndef _XESKELETONLOADER_H_
#define _XESKELETONLOADER_H_

#include "XeSkeleton.h"

namespace XE {

class CSkeletonLoader
{
public:
	CSkeletonLoader();
	virtual ~CSkeletonLoader();

	static CSkeleton* Load(const char* szName);

private:
	static bool LoadXml(const char* szPath);

	static bool LoadMesh(TiXmlNode* pMeshes);

	static bool LoadSharedGeometry(TiXmlElement* pGeometry);

	static bool LoadBoneAssignments(TiXmlElement* pBoneAssignments);
};

}

#endif //_XESKELETONLOADER_H_
