#include "stdafx.h"
#include "XeTimer.h"

namespace XE {

CTimer::CTimer() {
	m_nStartTime = GetTimeOfDay();
}

CTimer::~CTimer() {

}

void CTimer::Free() {

}

int CTimer::Time2Frame(float fTime) {
	return (int)(fTime * s_nFramePerSecond);
}

unsigned int CTimer::GetTime() {
	return GetTimeOfDay() - m_nStartTime;
}

unsigned int CTimer::GetTimeOfDay() {
	timeval tp;
	gettimeofday(&tp,  0);
	return (unsigned int)(tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

}
