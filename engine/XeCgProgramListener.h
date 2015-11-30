/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11-30
 */

#ifndef _XECGPROGRAMLISTENER_H_
#define _XECGPROGRAMLISTENER_H_

namespace XE {

class CCgProgramListener
{
public:
    virtual ~CCgProgramListener() {}

	virtual void OnComplete(GLuint nProgramID) = 0;
};

}

#endif //_XECGPROGRAMLISTENER_H_
