#include "stdafx.h"
#include "MyDataManager.h"
#include "MyGUI_DataFileStream.h"
#include "XeXFile.h"

namespace MyGUI {
	
	MyDataManager& MyDataManager::getInstance() {
		return *getInstancePtr();
	}

	MyDataManager* MyDataManager::getInstancePtr() {
		return static_cast<MyDataManager*>(DataManager::getInstancePtr());
	}
	
	MyDataManager::MyDataManager() :
		mIsInitialise(false) {
	}

	void MyDataManager::initialise() {
		mIsInitialise = true;
	}

	void MyDataManager::shutdown() {
		mIsInitialise = false;
	}

	IDataStream* MyDataManager::getData(const std::string& _name) {
		std::string filepath = getDataPath(_name);
		if (filepath.empty()) {
			return nullptr;
		}

		std::ifstream* stream = new std::ifstream();
		stream->open(filepath.c_str(), std::ios_base::binary);
		if (!stream->is_open()) {
			delete stream;
			return nullptr;
		}

		DataFileStream* data = new DataFileStream(stream);
		return data;
	}
	
	void MyDataManager::freeData(IDataStream* _data) {
		delete _data;
	}

	bool MyDataManager::isDataExist(const std::string& _name) {
		return XE::CXFile::IsExist(_name.c_str());
	}

	const VectorString& MyDataManager::getDataListNames(const std::string& _pattern) {
		static VectorString result;
        printf("getList: %s\n", _pattern.c_str());
		return result;
	}

	const std::string& MyDataManager::getDataPath(const std::string& _name) {
        static std::string path;
		path = XE::CXFile::GetWritablePath();
		path += _name;
        return path;
	}

} // namespace MyGUI
