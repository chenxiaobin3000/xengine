#include "stdafx.h"
#include "XeEngine.h"

namespace XE {

CEngine::CEngine () {

}
	
CEngine::~CEngine() {

}

bool CEngine::Init(const char* szResPath) {
	return false;
}

void CEngine::Free() {

}

bool CEngine::Reset() {
	return false;
}

bool CEngine::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef DISABLE_CULL
	glDisable(GL_CULL_FACE);
#else
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
#endif //DISABLE_CULL

	return true;
}
	
}
