/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 5
 */

#ifndef _MYGUIDATAMANAGER_H_
#define _MYGUIDATAMANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataManager.h"

namespace MyGUI {

class GLESDataManager : public DataManager
{
public:
   	GLESDataManager();

	void initialise();
	void shutdown();

	static GLESDataManager& getInstance() {
		return *getInstancePtr();
	}
	static GLESDataManager* getInstancePtr() {
		return static_cast<GLESDataManager*>(DataManager::getInstancePtr());
	}

	/** @see DataManager::getData(const std::string& _name) */
	virtual IDataStream* getData(const std::string& _name);

	/** @see DataManager::freeData */
	virtual void freeData(IDataStream* _data);

	/** @see DataManager::isDataExist(const std::string& _name) */
	virtual bool isDataExist(const std::string& _name);

	/** @see DataManager::getDataListNames(const std::string& _pattern) */
	virtual const VectorString& getDataListNames(const std::string& _pattern);

	/** @see DataManager::getDataPath(const std::string& _name) */
	virtual const std::string& getDataPath(const std::string& _name);

	/*internal:*/
	void addResourceLocation(const std::string& _name, bool _recursive);

private:
	struct ArhivInfo
	{
		std::wstring name;
		bool recursive;
	};
	typedef std::vector<ArhivInfo> VectorArhivInfo;
	VectorArhivInfo mPaths;

	bool mIsInitialise;
};

}

#endif // _MYGUIDATAMANAGER_H_
