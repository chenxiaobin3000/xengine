/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-03-25
 */

/*
json:

vertex_program vname {
    source vpath

    params {
        param_named_auto modelViewProj modelviewproj_matrix
		param_named_auto texelOffsets int 0
    }
}

fragment_program fname {
    source fpath

    default_params {
    }
}

material kname {
	technique t0 {
        pass p0 {
            vertex_program vname {
            }
            fragment_program fname {
            }
            texture_unit ShadowMap {
                纹理之后定
                tex_coord_set 0
                tex_address_mode clamp
                filtering none
            }
        }
    }
}
*/

#ifndef _XEMATERIALLOADER_H_
#define _XEMATERIALLOADER_H_

#include "XeMaterial.h"

namespace XE {

class CMaterialLoader
{
public:
	CMaterialLoader();
	virtual ~CMaterialLoader();

	static CMaterial* load(const char* szName);
};

}

#endif //_XEMATERIALLOADER_H_
