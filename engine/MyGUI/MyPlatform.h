/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-01-25
 */

#ifndef _MY_PLATFORM_H_
#define _MY_PLATFORM_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_LogManager.h"
#include "MyRenderManager.h"
#include "MyDataManager.h"

namespace MyGUI {

	class MyPlatform
	{
	public:
		MyPlatform();
		~MyPlatform();

		void initialise(const std::string& _logName = "MyGUI.log");
		void shutdown();

		MyRenderManager* getRenderManagerPtr();
		MyDataManager* getDataManagerPtr();

	private:
		bool mIsInitialise;
		MyRenderManager* mRenderManager;
		MyDataManager* mDataManager;
		LogManager* mLogManager;
	};

} // namespace MyGUI

#endif // _MY_PLATFORM_H_
