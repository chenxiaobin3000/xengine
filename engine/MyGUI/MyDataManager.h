/**
 * desc: 
 * auth: chenxiaobin
 * data: 2016-01-25
 */

#ifndef _MY_DATA_MANAGER_H_
#define _MY_DATA_MANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataManager.h"

namespace MyGUI {

	class MyDataManager :
		public DataManager
	{
	public:
		MyDataManager();

		void initialise();
		void shutdown();

		static MyDataManager& getInstance();
		static MyDataManager* getInstancePtr();

		/** @see DataManager::getData(const std::string& _name) */
		virtual IDataStream* getData(const std::string& _name);

		/** @see DataManager::freeData(IDataStream* _data */
		virtual void freeData(IDataStream* _data);
		
		/** @see DataManager::isDataExist(const std::string& _name) */
		virtual bool isDataExist(const std::string& _name);

		/** @see DataManager::getDataListNames(const std::string& _pattern) */
		virtual const VectorString& getDataListNames(const std::string& _pattern);

		/** @see DataManager::getDataPath(const std::string& _name) */
		virtual const std::string& getDataPath(const std::string& _name);

	private:
		bool mIsInitialise;
	};

} // namespace MyGUI

#endif // _MY_DATA_MANAGER_H_
