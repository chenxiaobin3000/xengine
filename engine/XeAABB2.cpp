#include "stdafx.h"
#include "XeAABB2.h"
#include "XeAABB.h"
#include "XeRay.h"

namespace XE {

CAABB2::CAABB2() {

}

CAABB2::CAABB2(CPoint& min, CPoint& max) : m_Min(min), m_Max(max) {

}

CAABB2::~CAABB2() {

}

CAABB2& CAABB2::operator=(const CAABB2& o) {
	m_Min = o.m_Min;  m_Max = o.m_Max;
	return *this;
}

void CAABB2::Set(CPoint& min, CPoint& max) {
	m_Min = min;  m_Max = max;
}

void CAABB2::Set(float x1, float y1, float x2, float y2) {
	m_Min.x = x1;  m_Min.y = y1;
	m_Max.x = x2;  m_Max.y = y2;
}

bool CAABB2::Intersect(const CPoint& v) {
	return m_Min.x <= v.x && v.x <= m_Max.x 
		&& m_Min.y <= v.y && v.y <= m_Max.y;
}

bool CAABB2::Intersect(const CVertex& v) {
	return m_Min.x <= v.x && v.x <= m_Max.x 
		&& m_Min.y <= v.z && v.z <= m_Max.y;
}

bool CAABB2::Intersect(const CVertex& v1, const CVertex& v2) {
	return true;
}

bool CAABB2::Intersect(const CRay& r) {
	float tmp = (float)(1.0f / r.d.x);
	float x1 = (m_Min.x - r.p.x) * tmp;
	float x2 = (m_Max.x - r.p.x) * tmp;

	float tmin = (std::min)(x1, x2);
	float tmax = (std::max)(x1, x2);

	tmp = (float)(1.0f / r.d.y);
	float y1 = (m_Min.y - r.p.y) * tmp;
	float y2 = (m_Max.y - r.p.y) * tmp;

	tmin = (std::max)(tmin, (std::min)(y1, y2));
	tmax = (std::min)(tmax, (std::max)(y1, y2));

	return (tmax >= tmin);
}

bool CAABB2::Intersect(const CAABB2& pIBB) {
	if (m_Max.x < pIBB.m_Min.x)
		return false;
	if (m_Max.y < pIBB.m_Min.y)
		return false;

	if (m_Min.x > pIBB.m_Max.x)
		return false;
	if (m_Min.y > pIBB.m_Max.y)
		return false;

	return true;
}

bool CAABB2::Intersect(const CAABB& pIBB) {
	if (m_Max.x < pIBB.m_Min.x)
		return false;
	if (m_Max.y < pIBB.m_Min.z)
		return false;

	if (m_Min.x > pIBB.m_Max.x)
		return false;
	if (m_Min.y > pIBB.m_Max.z)
		return false;

	return true;
}

bool CAABB2::Contain(const CPoint& v) {
	return m_Min.x <= v.x && v.x <= m_Max.x 
		&& m_Min.y <= v.y && v.y <= m_Max.y;
}

bool CAABB2::Contain(const CVertex& v) {
	return m_Min.x <= v.x && v.x <= m_Max.x 
		&& m_Min.y <= v.z && v.z <= m_Max.y;
}

bool CAABB2::Contain(const CVertex& v1, const CVertex& v2) {
	return true;
}

bool CAABB2::Contain(const CRay& r) {
	return Contain(r.p);
}

bool CAABB2::Contain(const CAABB2& pIBB) {
	return m_Min.x <= pIBB.m_Min.x 
		&& m_Min.y <= pIBB.m_Min.y 
		&& pIBB.m_Max.x <= m_Max.x 
		&& pIBB.m_Max.y <= m_Max.y;
}

bool CAABB2::Contain(const CAABB& pIBB) {
	return m_Min.x <= pIBB.m_Min.x 
		&& m_Min.y <= pIBB.m_Min.z 
		&& pIBB.m_Max.x <= m_Max.x 
		&& pIBB.m_Max.z <= m_Max.y;
}

void CAABB2::Render(byte r, byte g, byte b) {
/*	CVertex v1, v2;

	v1.Set(m_Min.x, 0, m_Min.y);
	v2.Set(m_Max.x, 0, m_Min.y);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, 0, m_Min.y);
	v2.Set(m_Min.x, 0, m_Max.y);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Max.x, 0, m_Min.y);
	v2.Set(m_Max.x, 0, m_Max.y);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, 0, m_Max.y);
	v2.Set(m_Max.x, 0, m_Max.y);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);*/
}

void CAABB2::SetPosition(const CPoint& v) {
	SetPosition(v.x, v.y);
}

void CAABB2::SetPosition(float x, float y) {
	float lx = m_Max.x - m_Min.x;
	float ly = m_Max.y - m_Min.y;
	m_Min.x = x;	m_Min.y = y;
	m_Max.x = x+lx;	m_Max.y = y+ly;
}

void CAABB2::Move(const CPoint& v) {
	Move(v.x, v.y);
}

void CAABB2::Move(float x, float y) {
	m_Min.x += x;	m_Min.y += y;
	m_Max.x += x;	m_Max.y += y;
}

void CAABB2::SetSize(const CPoint& v) {
	SetSize(v.x, v.y);
}

void CAABB2::SetSize(float x, float y) {
	m_Max.x = m_Min.x + x;
	m_Max.y = m_Min.y + y;
}

}
