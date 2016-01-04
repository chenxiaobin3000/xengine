#include "stdafx.h"
#include "XeVoronoi.h"
#include "XeMath.h"

namespace XE {

#define DISTANCE ManhattanDistance
const float CVoronoi::s_fInfinite = MAX_FLOAT;

CVoronoi::CVoronoi() {

}

CVoronoi::~CVoronoi() {

}

void CVoronoi::AddPoint(int x, int y, byte data) {
	SPoint p;
	p.x = x;
	p.y = y;
	p.data = data;
	m_List.XEPUSH(p);
}

void CVoronoi::Clear() {
	m_List.clear();
}

void CVoronoi::Generate(int nWidth, int nHeight, byte* szData) {
	float fDistance, fTmp;
	auto end = m_List.end();
	for (int j=0; j<nHeight; ++j) {
		for (int i=0; i<nWidth; ++i) {
			fDistance = CVoronoi::s_fInfinite;
			auto ite = m_List.begin();
			for (; end!=ite; ++ite) {
				fTmp = DISTANCE((float)i, (float)j, (float)ite->x, (float)ite->y);
				if (fTmp < fDistance) {
					szData[i+nWidth*j] = ite->data;
					fDistance = fTmp;
				}
			}
		}
	}
}

float CVoronoi::EuclideanDistance(float p1x, float p1y, float p2x, float p2y) {
	return sqrt((p1x-p2x)*(p1x-p2x)+(p1y-p2y)*(p1y-p2y));
}

float CVoronoi::ManhattanDistance(float p1x, float p1y, float p2x, float p2y) {
	return fabs(p1x-p2x) + fabs(p1y-p2y);
}

}
