#include "stdafx.h"
#include "MyDataManager.h"
#include "MyGUI_DataFileStream.h"
#include "XeXFile.h"

namespace MyGUI {
	
    const char* MyDataManager::s_szPath = "mygui/";
    
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
        bool bRet = false;
        if (std::string::npos != _name.find(".png")) {
            std::string str = "texture/";
            str += _name;
            bRet = XE::CXFile::IsExist(str.c_str());
        } else {
            bRet = XE::CXFile::IsExist(_name.c_str());
        }
        if (!bRet) {
            printf("mygui data no found: %s\n", _name.c_str());
        }
		return bRet;
	}

	const VectorString& MyDataManager::getDataListNames(const std::string& _pattern) {
		static VectorString result;
        printf("mygui get list: %s\n", _pattern.c_str());
		return result;
	}

	const std::string& MyDataManager::getDataPath(const std::string& _name) {
        static std::string path;
		path = XE::CXFile::GetWritablePath();
        path += s_szPath;
		path += _name;
        return path;
	}

} // namespace MyGUI
