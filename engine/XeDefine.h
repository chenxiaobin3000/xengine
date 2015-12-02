/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _XEDEFINE_H_
#define _XEDEFINE_H_

#define _DEBUG

// 辅助函数宏
#ifdef _DEBUG
#	define XELOG            XE::XLog
#	define XEASSERT(x)     assert(x)
#	define XENEW(x)        new x
#	define XEDELETE(x)     delete x; x=NULL
#	define XEPUSH(x)       push_back(x)
#	define XEINSERT(x)     insert(x)
#else
#	define XELOG(...)
#	define XEASSERT(x)
#	define XENEW(x)        new x
#	define XEDELETE(x)     delete x; x=NULL
#	define XEPUSH(x)       push_back(x)
#	define XEINSERT(x)     insert(x)
#endif //_DEBUG

namespace XE {

template<typename T>
inline static void FreeList(std::vector<T*>& list) {
	auto ite = list.begin();
	auto end = list.end();
	for (; end!=ite; ++ite) {
		delete(*ite);
	}
	list.clear();
}

template<typename T>
inline static void FreeList(std::list<T*>& list) {
	auto ite = list.begin();
	auto end = list.end();
	for (; end!=ite; ++ite) {
		delete(*ite);
	}
	list.clear();
}

}

#endif //_XEDEFINE_H_
