/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-25
 */

#ifndef _XESKINRENDEROBJECTLOADER_H_
#define _XESKINRENDEROBJECTLOADER_H_

#include "XeSkinRenderObject.h"

namespace XE {

class CSkinRenderObjectLoader
{
public:
	CSkinRenderObjectLoader();
	virtual ~CSkinRenderObjectLoader();
	
	static CSkinRenderObject* Load(const char* szName);

private:
	static bool LoadXml(const char* szPath);

	static bool LoadMesh(TiXmlNode* pMeshes);

	static bool LoadSharedGeometry(TiXmlElement* pGeometry);

	static bool LoadBoneAssignments(TiXmlElement* pBoneAssignments);
};

}

#endif //_XESKINRENDEROBJECTLOADER_H_
