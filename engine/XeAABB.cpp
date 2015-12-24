#include "stdafx.h"
#include "XeAABB.h"
#include "XeRay.h"
#include "XeMathDef.h"

namespace XE {

const float CAABB::s_fMax = MAX_FLOAT;

CAABB::CAABB() {

}

CAABB::CAABB(const CVertex& min, const CVertex& max) : m_Min(min), m_Max(max) {

}

CAABB::~CAABB() {

}

CAABB& CAABB::operator=(const CAABB& o) {
	m_Min = o.m_Min;  m_Max = o.m_Max;
	return *this;
}

void CAABB::Set(CVertex& min, CVertex& max) {
	m_Min = min;  m_Max = max;
}

bool CAABB::Intersect(const CVertex& v) {
	return m_Min.x <= v.x && v.x <= m_Max.x 
		&& m_Min.y <= v.y && v.y <= m_Max.y 
		&& m_Min.z <= v.z && v.z <= m_Max.z;
}

bool CAABB::Intersect(const CVertex& v1, const CVertex& v2) {
	return false;
}

bool CAABB::Intersect(const CRay& r) {
	float tmp;
	float tmin = -MAX_FLOAT;
	float tmax = MAX_FLOAT;

	if (IsFloatEqual(r.d.x, 0.0f)) {
		// 与yz面平行
		if (r.p.x < m_Min.x || r.p.x > m_Max.x) {
			return false;
		}
	} else {
		tmp = (float)(1.0f / r.d.x);
		float x1 = (m_Min.x - r.p.x) * tmp;
		float x2 = (m_Max.x - r.p.x) * tmp;
		tmin = (std::min)(x1, x2);
		tmax = (std::max)(x1, x2);

		if (tmax < tmin) {
			return false;
		}
	}

	if (IsFloatEqual(r.d.y, 0.0f)) {
		// 与xz面平行
		if (r.p.y < m_Min.y || r.p.y > m_Max.y) {
			return false;
		}
	} else {
		tmp = (float)(1.0f / r.d.y);
		float y1 = (m_Min.y - r.p.y) * tmp;
		float y2 = (m_Max.y - r.p.y) * tmp;
		tmin = (std::max)(tmin, (std::min)(y1, y2));
		tmax = (std::min)(tmax, (std::max)(y1, y2));

		if (tmax < tmin) {
			return false;
		}
	}

	if (IsFloatEqual(r.d.z, 0.0f)) {
		// 与xy面平行
		if (r.p.z < m_Min.z || r.p.z > m_Max.z) {
			return false;
		}
	} else {
		tmp = (float)(1.0f / r.d.z);
		float z1 = (m_Min.z - r.p.z) * tmp;
		float z2 = (m_Max.z - r.p.z) * tmp;
		tmin = (std::max)(tmin, (std::min)(z1, z2));
		tmax = (std::min)(tmax, (std::max)(z1, z2));
	}

	return (tmax >= tmin);
}

bool CAABB::Intersect(const CAABB& pIBB) {
	if (m_Max.x < pIBB.m_Min.x)
		return false;
	if (m_Max.y < pIBB.m_Min.y)
		return false;
	if (m_Max.z < pIBB.m_Min.z)
		return false;

	if (m_Min.x > pIBB.m_Max.x)
		return false;
	if (m_Min.y > pIBB.m_Max.y)
		return false;
	if (m_Min.z > pIBB.m_Max.z)
		return false;

	return true;
}

bool CAABB::Intersect(const COBB& pIBB) {
	return false;
}

bool CAABB::Contain(const CVertex& v) {
	return m_Min.x <= v.x && v.x <= m_Max.x 
		&& m_Min.y <= v.y && v.y <= m_Max.y 
		&& m_Min.z <= v.z && v.z <= m_Max.z;
}

bool CAABB::Contain(const CVertex& v1, const CVertex& v2) {
	return false;
}

bool CAABB::Contain(const CRay& r) {
	return Contain(r.p);
}

bool CAABB::Contain(const CAABB& pIBB) {
	return m_Min.x <= pIBB.m_Min.x 
		&& m_Min.y <= pIBB.m_Min.y 
		&& m_Min.z <= pIBB.m_Min.z 
		&& pIBB.m_Max.x <= m_Max.x 
		&& pIBB.m_Max.y <= m_Max.y 
		&& pIBB.m_Max.z <= m_Max.z;
}

bool CAABB::Contain(const COBB& pIBB) {
	return false;
}

void CAABB::Render(byte r, byte g, byte b) {
	CVertex v1, v2;

	// 下层
	v1.Set(m_Min.x, m_Min.y, m_Min.z);
	v2.Set(m_Max.x, m_Min.y, m_Min.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, m_Min.y, m_Min.z);
	v2.Set(m_Min.x, m_Max.y, m_Min.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Max.x, m_Min.y, m_Min.z);
	v2.Set(m_Max.x, m_Max.y, m_Min.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, m_Max.y, m_Min.z);
	v2.Set(m_Max.x, m_Max.y, m_Min.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	// 上层
	v1.Set(m_Min.x, m_Min.y, m_Max.z);
	v2.Set(m_Max.x, m_Min.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, m_Min.y, m_Max.z);
	v2.Set(m_Min.x, m_Max.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Max.x, m_Min.y, m_Max.z);
	v2.Set(m_Max.x, m_Max.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, m_Max.y, m_Max.z);
	v2.Set(m_Max.x, m_Max.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	// 边柱
	v1.Set(m_Min.x, m_Min.y, m_Min.z);
	v2.Set(m_Min.x, m_Min.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Min.x, m_Max.y, m_Min.z);
	v2.Set(m_Min.x, m_Max.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Max.x, m_Min.y, m_Min.z);
	v2.Set(m_Max.x, m_Min.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);

	v1.Set(m_Max.x, m_Max.y, m_Min.z);
	v2.Set(m_Max.x, m_Max.y, m_Max.z);
	CLineBuffer::GetSingleton().DrawLine(v1, v2, r, g, b);
}

void CAABB::SetPosition(const CVertex& v) {
	SetPosition(v.x, v.y, v.z);
}

void CAABB::SetPosition(float x, float y, float z) {
	float lx = m_Max.x - m_Min.x;
	float ly = m_Max.y - m_Min.y;
	float lz = m_Max.z - m_Min.z;
	m_Min.x = x;	m_Min.y = y;	m_Min.z = z;
	m_Max.x = x+lx;	m_Max.y = y+ly;	m_Max.z = z+lz;
}

void CAABB::Move(const CVertex& v) {
	Move(v.x, v.y, v.z);
}

void CAABB::Move(float x, float y, float z) {
	m_Min.x += x;	m_Min.y += y;	m_Min.z += z;
	m_Max.x += x;	m_Max.y += y;	m_Max.z += z;
}

}
