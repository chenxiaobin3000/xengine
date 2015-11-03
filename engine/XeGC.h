/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _XEGC_H_
#define _XEGC_H_

#include "XePool.h"

namespace XE {

template<typename T>
class CGC
{
private:
	template<typename TC>
	class CGCCount :
		public CPool<CGCCount<TC>, 256>
	{
	public:
		CGCCount(TC* p) : m_count(0), m_clear(false), m_ptr(p) {}

		virtual ~CGCCount() {
			delete m_ptr;
		}

		void Inc() {
			++m_count;
		}

		void Dec() {
			if (0 >= --m_count) {
				m_clear=true;
			}
		}

	public:
		int					m_count;
		bool				m_clear;
		TC*					m_ptr;
	};

private:
    // vs 和 gcc 都需要 typename，所以不用 TYPENAME 宏
	typedef std::map<int, CGCCount<T>*>					GCCMap;
	typedef typename GCCMap::value_type					GCCMapValue;

	typedef std::map<T*, int>							GCPMap;
	typedef typename GCPMap::value_type					GCPMapValue;

public:
	CGC() : m_nKeyIndex(0) {}

	virtual ~CGC() {
		m_CountMap.clear();
		m_PtrMap.clear();
	}

	int Reg() {
		T* p = NEW_LOG(T);
		return Reg(p);
	}

	int Reg(T* p) {
		CGCCount<T>* pT = NEW_LOG(CGCCount<T>(p));
		m_CountMap.INSERT(GCCMapValue(m_nKeyIndex, pT));
		m_PtrMap.INSERT(GCPMapValue(p, m_nKeyIndex));
		return m_nKeyIndex++;
	}

	T* Get(int key) {
		auto ite = m_CountMap.find(key);
		if (m_CountMap.end() != ite) {
			ite->second->Inc();
			return ite->second->m_ptr;
		}
		return NULL;
	}

	void Free(T* p) {
		auto ite = m_PtrMap.find(p);
		if (m_PtrMap.end() != ite) {
			auto ite1 = m_CountMap.find(ite->second);
			if (m_CountMap.end() != ite1) {
				ite1->second->Dec();
			}
		}
	}

	void Collect() {
		auto ite = m_CountMap.begin();
		auto end = m_CountMap.end();
		while (end != ite) {
			if (ite->second->m_clear) {
				auto ite1 = m_PtrMap.find(ite->second->m_ptr);
				if (m_PtrMap.end() != ite1) {
					m_PtrMap.erase(ite1);
				}
				delete(ite->second);
				ite = m_CountMap.erase(ite);
				end = m_CountMap.end();
			} else {
				++ite;
			}
		}
	}

private:
	GCCMap		m_CountMap;
	GCPMap		m_PtrMap;
	int			m_nKeyIndex;
};

}

#endif //_XEGC_H_
