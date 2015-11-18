/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _XEDEFINE_H_
#define _XEDEFINE_H_

// 辅助函数宏
#ifdef _DEBUG
#	define XELOG		XE::XLog
#	define XEASSERT		assert
#	define NEW_LOG(x)	new x//; XELOG("new file: %s:%d\n", __FILE__, __LINE__)
#	define PUSH(x)		push_back(x)//; XELOG("push file: %s:%d\n", __FILE__, __LINE__)
#	define INSERT(x)	insert(x)//; XELOG("insert file: %s:%d\n", __FILE__, __LINE__)
#else
#	define XELOG
#	define XEASSERT
#	define NEW_LOG(x)	new x
#	define PUSH(x)		push_back(x)
#	define INSERT(x)	insert(x)
#endif //_DEBUG

#endif //_XEDEFINE_H_
