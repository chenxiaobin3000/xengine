#include "stdafx.h"
#include "XeEngine.h"
#include "XeConfig.h"

namespace XE {

CEngine::CEngine () {

}
	
CEngine::~CEngine() {

}

bool CEngine::Init() {
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

   	if (CConfig::GetDisableCull()) {
		glDisable(GL_CULL_FACE);
	} else {
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	// 开启阴影
/*	if (CConfig::GetUseShadow()) {
		setTechnique(shadow);
		shadow_list = getShadowList();
		foreach (shadow) {
			foreach (object) {
				object->Begin();
				object->Render(Camera);
				object->End();
			}
		}
	}

	setTechnique(normal);
	camera = getMainCamera();
	camera->Lookat();

	foreach (object) {
		object->Begin();
		object->Render(camera);
		object->End();
	}

	render_list->render();
*/
	return true;
}

}
