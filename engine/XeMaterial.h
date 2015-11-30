/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */
/*
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

#ifndef _XEMATERIAL_H_
#define _XEMATERIAL_H_

#include "XeTechnique.h"
#include "XeTechniqueManager.h"

namespace XE {

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	CTechnique* GetTechnique(ETechniqueType type);

private:
	std::vector<CTechnique*>	m_pTechniqueList;
};

}

#endif //_XEMATERIAL_H_
