/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-25
 */

/*
材质模版(json)
[
    {
        "顶点着色器列表": "",
        "type": "vertex_program",
        "list": [
            {
                "name": "",
                "source": "",
                "params": [
                    "ModelViewProj",
                    "AmbiColor"
                ]
            }
        ]
    },
    {
        "片段着色器列表": "",
        "type": "fragment_program",
        "list": [
            {
                "name": "",
                "source": "",
                "params": [
                    "ModelViewProj",
                    "AmbiColor"
                ]
            }
        ]
    },
    {
        "材质，list是技术列表，从上到下加载": "",
        "type": "material",
        "list": [
            {
                "技术(高端配置)，list是pass列表": "",
                "type": "technique",
                "list": [
                    {
                        "pass，第一个": "",
						"type": "pass",
                        "vertex_program": "",
                        "fragment_program": "",
                        "颜色格式": "rgba",
                        "diffuse": [0.2,0.2,0.2,1.0],
                        "ambient": [0.2,0.2,0.2,1.0],
                        "specular": [1.0,1.0,1.0,1.0],
                        "emissive": [1.0,1.0,1.0,1.0],
                        "texture_unit": {
                            "texture": "",
                            "filter_mode": "",
                            "address_mode": ""
                        }
                    },
                    {
                        "pass，第二个": ""
                    }
                ]
            },
            {
                "技术(低端配置)": ""
            }
        ]
    }
]
*/

#ifndef _XEMATERIALLOADER_H_
#define _XEMATERIALLOADER_H_

#include "XeMaterial.h"
#include "XeCg.h"

namespace XE {

class CMaterialLoader
{
public:
	CMaterialLoader();
	virtual ~CMaterialLoader();

	static CMaterial* Load(const char* szName);
    
private:
    static CCg* ParseVertex(const char* szName, Json::Value& root);
    
    static CCg* ParseFragment(const char* szName, Json::Value& root);
    
    static CPass* ParsePass(Json::Value& json, Json::Value& root);
};

}

#endif //_XEMATERIALLOADER_H_
