#include "stdafx.h"
#include "XeTriangle.h"
#include "XeMath.h"

namespace XE {

CTriangle::CTriangle() : m_p1(0,0), m_p2(0,0), m_p3(0,0) {

}

CTriangle::CTriangle(float x1, float y1, float x2, float y2, float x3, float y3) : 
	m_p1(x1,y1), m_p2(x2,y2), m_p3(x3,y3) {

}

CTriangle::~CTriangle() {

}

// 射线法（x轴正方向）
bool CTriangle::Contain(CPoint& p, bool bInSize) {
	int cnt = 0;

	// 是否交于边
	if (IsFloatEqual((p.x-m_p1.x)*(m_p2.y-m_p1.y), (p.y-m_p1.y)*(m_p2.x-m_p1.x))) {
		return bInSize;
	}
	if (IsFloatEqual((p.x-m_p2.x)*(m_p3.y-m_p2.y), (p.y-m_p2.y)*(m_p3.x-m_p2.x))) {
		return bInSize;
	}
	if (IsFloatEqual((p.x-m_p3.x)*(m_p1.y-m_p3.y), (p.y-m_p3.y)*(m_p1.x-m_p3.x))) {
		return bInSize;
	}

	// 边1 - 平行x轴
	if (!IsFloatEqual(m_p1.y, m_p2.y)) {
		// 上方
		if (p.y <= m_p1.y || p.y <= m_p2.y) {
			// 下方（上闭下开）
			if (p.y > m_p1.y || p.y > m_p2.y) {
				// 右方
				if (p.x <= m_p1.x || p.x <= m_p2.x) {
					if (p.x < (m_p1.x + (m_p2.x - m_p1.x)*(p.y - m_p1.y)/(m_p2.y - m_p1.y))) {
						++cnt;
					}
				}
			}
		}
	}

	// 边2 - 平行x轴
	if (!IsFloatEqual(m_p2.y, m_p3.y)) {
		// 上方
		if (p.y <= m_p2.y || p.y <= m_p3.y) {
			// 下方（上闭下开）
			if (p.y > m_p2.y || p.y > m_p3.y) {
				// 右方
				if (p.x <= m_p2.x || p.x <= m_p3.x) {
					if (p.x < (m_p2.x + (m_p3.x - m_p2.x)*(p.y - m_p2.y)/(m_p3.y - m_p2.y))) {
						++cnt;
					}
				}
			}
		}
	}

	// 边3 - 平行x轴
	if (!IsFloatEqual(m_p3.y, m_p1.y)) {
		// 上方
		if (p.y <= m_p3.y || p.y <= m_p1.y) {
			// 下方（上闭下开）
			if (p.y > m_p3.y || p.y > m_p1.y) {
				// 右方
				if (p.x <= m_p3.x || p.x <= m_p1.x) {
					if (p.x < (m_p3.x + (m_p1.x - m_p3.x)*(p.y - m_p3.y)/(m_p1.y - m_p3.y))) {
						++cnt;
					}
				}
			}
		}
	}
	return (cnt%2==1) ? true : false;
}

}
