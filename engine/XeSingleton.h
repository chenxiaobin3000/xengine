/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace XE {

template <typename T>
class CSingleton
{
public:
	static T& GetSingleton() {
		return s_Instance;
	}

	static T* GetSingletonPtr() {
		return &s_Instance;
	}

	// 强制提供释放方法
	virtual void Free() = 0;

protected:
	CSingleton() {}

	virtual ~CSingleton() {}

private:
	CSingleton(const CSingleton<T>&) {}

	CSingleton& operator=(const CSingleton<T>&) {}

protected:
	static T s_Instance;
};

template<typename T>
T CSingleton<T>::s_Instance;

}

#endif //_SINGLETON_H_
