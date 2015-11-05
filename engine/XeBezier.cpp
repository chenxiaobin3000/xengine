#include "stdafx.h"
#include "XeBezier.h"

namespace XE {

CBezier3::CBezier3(EPower p) : m_ePower(p) {

}

CBezier3::~CBezier3() {

}

void CBezier3::SetPoint(const CVertex& v, int index) {
	if (index < s_nBezierNum) {
		m_v[index] = v;
	}
}

CVertex& CBezier3::GetValue(float t) {
	float f[s_nBezierNum];
	float tn = 1.0f - t;
	m_Result.Identity();

	switch (m_ePower) {
	case E_Power2: // y = (1-t)^2*p0 + 2t(1-t)*p1 + t^2*p2
		{
			f[0] = tn*tn;
			f[1] = 2*t*tn;
			f[2] = t*t;
		}
		break;

	case E_Power3: // y = (1-t)^3*p0 + 3t(1-t)^2*p1 + 3t^2(1-t)*p2 + t^3*p3
		{
			f[0] = tn*tn*tn;
			f[1] = 3*t*tn*tn;
			f[2] = 3*t*t*tn;
			f[3] = t*t*t;
		}
		break;

	default:
		return m_Result;
	}

	CVertex tmp;
	for (int i=0; i<m_ePower+1; ++i) {
		tmp = m_v[i];
		tmp.MultNum(f[i]);
		m_Result += tmp;
	}

	return m_Result;
}

void CBezier3::GetValue(CVertexList& list) {
	int size = (int)list.size();
	float t = (float)(1.0 / size);
	for (int i=0; i<size; ++i) {
		list[i] = GetValue(t*i);
	}
}

}
