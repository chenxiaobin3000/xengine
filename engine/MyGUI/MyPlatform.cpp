#include "stdafx.h"
#include "MyPlatform.h"

namespace MyGUI {

	MyPlatform::MyPlatform() :
		mIsInitialise(false) {
		mRenderManager = new MyRenderManager();
		mDataManager = new MyDataManager();
		mLogManager = new LogManager();
	}

	MyPlatform::~MyPlatform() {
		delete mRenderManager;
		delete mDataManager;
		delete mLogManager;
	}

	void MyPlatform::initialise(const std::string& _logName) {
		mIsInitialise = true;

		if (!_logName.empty()) {
			LogManager::getInstance().createDefaultSource(_logName);
		}

		mRenderManager->initialise();
		mDataManager->initialise();
	}

	void MyPlatform::shutdown() {
		mIsInitialise = false;

		mRenderManager->shutdown();
		mDataManager->shutdown();
	}

	MyRenderManager* MyPlatform::getRenderManagerPtr() {
		return mRenderManager;
	}

	MyDataManager* MyPlatform::getDataManagerPtr() {
		return mDataManager;
	}

} // namespace MyGUI
