/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-25
 */

/*
带骨骼动画模型格式
<?xml version="1.0" encoding="UTF-8"?>
<mesh>
    <sharedgeometry vertexcount="0">
        <vertexbuffer>
            <vertex>
                <position z="0.00" y="0.00" x="0.00"/>
                <normal z="0.00" y="0.00" x="0.00"/>
                <texcoord v="0.00" u="0.00"/>
            </vertex>
            ...
        </vertexbuffer>
    </sharedgeometry>
    <submeshes>
        <submesh material="mate_name">
            <faces count="0">
                <face v1="0" v2="1" v3="2"/>
                ...
            </faces>
        </submesh>
		...
    </submeshes>
    <boneassignments>
        <vertexboneassignment boneindex="0" weight="0.00" vertexindex="0"/> 
		...
    </boneassignments>
	<skeletonlink name="xxx.skeleton"/>
</mesh>
*/

#ifndef _XESKINRENDEROBJECTLOADER_H_
#define _XESKINRENDEROBJECTLOADER_H_

#include "XeSkinRenderObject.h"
#include "XeRenderObjectLoader.h"

namespace XE {

class CSkinRenderObjectLoader : public CRenderObjectLoader
{
public:
	CSkinRenderObjectLoader();
	virtual ~CSkinRenderObjectLoader();
	
	static CSkinRenderObject* Load(const char* szName);

private:
	static bool LoadXml(const char* szPath);

	static bool LoadBoneAssignments(tinyxml2::XMLElement* pBoneAssignments, CSkinRenderObject* pRenderObject);

private:
    static const float			s_fSkinMin;
};

}

#endif //_XESKINRENDEROBJECTLOADER_H_
