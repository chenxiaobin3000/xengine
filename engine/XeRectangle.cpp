#include "stdafx.h"
#include "XeRectangle.h"

namespace XE {

CRect::CRect() : m_p1(0,0), m_p2(0,0) {

}

CRect::CRect(float x1, float y1, float x2, float y2) : m_p1(x1,y1), m_p2(x2,y2) {

}

CRect::~CRect() {

}

void CRect::Set(float x1, float y1, float x2, float y2) {
	m_p1.Set(x1, y1);	m_p2.Set(x2, y2);
}

float CRect::GetWidth() {
	return m_p2.x - m_p1.x;
}

float CRect::GetHeight() {
	return m_p2.y - m_p1.y;
}

bool CRect::Contain(CPoint& p, bool bInSize) {
	// 是否交于边
	if ((p.x == m_p1.x || p.x == m_p2.x) 
	&& (p.y == m_p1.y || p.y == m_p2.y)) {
		return bInSize;
	}

	// 是否在矩形内
	if (p.x >= m_p1.x && p.x <= m_p2.x 
	&&  p.y >= m_p1.y && p.y <= m_p2.y) {
		return true;
	} else {
		return false;
	}
}

bool CRect::Contain(CTriangle& Tri, bool bInSize) {
	if (!Contain(Tri.m_p1, bInSize)) {
		return false;
	}
	if (!Contain(Tri.m_p2, bInSize)) {
		return false;
	}
	if (!Contain(Tri.m_p3, bInSize)) {
		return false;
	}
	return true;
}

}
