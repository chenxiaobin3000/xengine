/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _XETIME_H_
#define _XETIME_H_

#include "XeSingleton.h"

namespace XE {

class CTimer :
	public CSingleton<CTimer>
{
	friend class CSingleton<CTimer>;

public:
	static const int s_nFramePerSecond = 24;

private:
	CTimer();
	virtual ~CTimer();

public:
	virtual void Free();
	
	static int Time2Frame(float fTime);

	unsigned int GetTime();

	unsigned int GetTimeOfDay();

private:
	unsigned int				m_nStartTime;
};

}

#endif //_XETIME_H_
