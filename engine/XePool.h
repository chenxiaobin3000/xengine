/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XEPOOL_H_
#define _XEPOOL_H_

namespace XE {

// 分配器
template<typename T, int size>
class CAlloc
{
private:
	struct SPtr {
		byte*	ptr;
		int		num;

		SPtr(byte* p, int s) : ptr(p), num(s) {}
	};

private:
	typedef std::vector<T*>								PoolList;
	typedef std::map<T*, T*>							PoolMap;
	typedef std::vector<SPtr>							PtrList;

public:
	CAlloc() {
		_Alloc(size);
	}

	virtual ~CAlloc() {
		auto ite = m_ptr.begin();
		auto end = m_ptr.end();
		for (; end!=ite; ++ite) {
			delete(ite->ptr);
		}
		m_using.clear();
		m_reserve.clear();
		m_ptr.clear();
	}

	bool _Alloc(int num = 0) {
		if (m_reserve.empty()) {
			if (0 == num) {
				num = (int)m_using.size();
			}
			byte* pMem = XENEW(byte[sizeof(T)*num]);
			if (!pMem) {
				return false;
			}
			m_ptr.XEPUSH(SPtr(pMem, num));
			T* ptr = (T*)pMem;
			for (int i=0; i<num; ++i) {
				m_reserve.XEPUSH(ptr++);
			}
		}
		return true;
	}

	void* Alloc() {
		if (!_Alloc()) {
			return NULL;
		}
		T* ptr = m_reserve.back();
		m_reserve.pop_back();
		m_using.XEINSERT(TYPENAME PoolMap::value_type(ptr, ptr));
		return ptr;
	}

	void Free(void* p) {
		auto ite = m_using.find((T*)p);
		if (m_using.end() != ite) {
			m_reserve.XEPUSH(ite->first);
			m_using.erase(ite);
		}
	}

private:
	PoolMap			m_using;
	PoolList		m_reserve;
	PtrList			m_ptr;
};

// 池
template<typename T, int size>
class CPool
{
public:
	virtual ~CPool() {}

	void* operator new(size_t s) {
		return s_Alloc.Alloc();
	}

	void operator delete(void* p) {
		s_Alloc.Free(p);
	}

private:
	// 不支持数组申请
    void* operator new[](size_t s) { void* p = NULL; return p; }
	void operator delete[](void* p) {}

protected:
	static CAlloc<T, size>			s_Alloc;
};

template<typename T, int size>
CAlloc<T,size>						CPool<T,size>::s_Alloc;

}

#endif //_XEPOOL_H_
