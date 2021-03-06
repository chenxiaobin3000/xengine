/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-21
 */

#ifndef _XEENGINE_H_
#define _XEENGINE_H_

#include "XeSingleton.h"

namespace MyGUI {
    class Gui;
    class MyPlatform;
}

namespace XE {

class CEngine :
   	public CSingleton<CEngine>
{
	friend class CSingleton<CEngine>;
	
private:
	CEngine();
	virtual ~CEngine();

public:
	bool Init(int width, int height);

	virtual void Free();

	bool Reset();

	bool Render();

private:
    MyGUI::Gui*					m_pGUI;
    MyGUI::MyPlatform*			m_pGUIPlatform;
};

}

#endif //_XEENGINE_H_
