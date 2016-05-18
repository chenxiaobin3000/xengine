/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-04- 1
 */

/*
静态模型格式
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
    </submeshes>
</mesh>
*/

#ifndef _XERENDEROBJECTLOADER_H_
#define _XERENDEROBJECTLOADER_H_

#include "XeRenderObject.h"
#include "XeVertexBuffer.h"

namespace XE {

class CRenderObjectLoader
{
	friend class CSkinRenderObjectLoader;
	
public:
	CRenderObjectLoader();
	virtual ~CRenderObjectLoader();

	static CRenderObject* Load(const char* szName);

private:
	static CRenderObject* LoadXml(const char* szPath);

    static bool LoadSharedGeometry(tinyxml2::XMLElement* pGeometry, CVertexBuffer* pVertexBuffer);

    static bool LoadMesh(tinyxml2::XMLElement* pMesh, CRenderObject* pRenderObject, CVertexBuffer* pVertexBuffer);
};

}

#endif //_XERENDEROBJECTLOADER_H_
