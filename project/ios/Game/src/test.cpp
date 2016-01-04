//
//  test.cpp
//  Game
//
//  Created by chenxiaobin on 15/10/16.
//  Copyright © 2015年 xe. All rights reserved.
//

#include "test.h"
#include "../../../../engine/app/ios/stdafx.h"
#include "../../../../engine/XeVertexBuffer.h"
#include "../../../../engine/XeCgProgram.h"
#include "../../../../engine/XePass.h"
#include "../../../../engine/XeCamera.h"

using namespace XE;

static CCgProgram* s_program = NULL;
static CCamera* s_camera = NULL;
static CRenderObject* s_object = NULL;

void MakeCube();
void InitCg();
void Rotate();

void InitTest() {
    XELOG("init test");
	//static CRenderScene CRenderScene;
	//static CCamera camera;
	//scene.Render(camera);

    s_program = new CCgProgram;
	s_object = new CRenderObject;

	CVertex f(0,0,-1);
	CPoint s(480,320);
	s_camera = new CCamera(f, s, 10, 500);
    s_camera->SetPosition(0, 0, 1);
    
    MakeCube();
    InitCg();
}

void RenderTest() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    
    glViewport(0, 0, (GLsizei)480, (GLsizei)320);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Rotate();
	s_camera->Lookat();

	// -- render object --
	//for () {
        s_object->Render(s_camera);
	//}
	
	// -- render buffer --
    s_program->Bind(NULL);
	//for (object) {
        s_program->SetTarget(s_object);
        // for (object->buffer) {
		    s_object->Draw();
        //}
	//}
    s_program->UnBind();
}

void MakeCube() {
    XELOG("make cube");
    float* pVertexs;
    float* pTexcoords;
    float* pNormals;
    unsigned int* pIndexs;
    CVertexBuffer* buffer = new CVertexBuffer;
    buffer->SetCount(6, 0);
    if (buffer->Lock(pVertexs, pTexcoords, pNormals, pIndexs)) {
        pVertexs[0] = 0.0f; pVertexs[1] = 0.0f; pVertexs[2] = 0.0f;
        pVertexs[3] = 0.0f; pVertexs[4] = 1.0f; pVertexs[5] = 0.0f;
        pVertexs[6] = 1.0f; pVertexs[7] = 0.0f; pVertexs[8] = 0.0f;
        pTexcoords[0] = 0.0f; pTexcoords[1] = 1.0f;
        pTexcoords[2] = 0.0f; pTexcoords[3] = 0.0f;
        pTexcoords[4] = 1.0f; pTexcoords[5] = 1.0f;
        ZeroMemory(pNormals, sizeof(float)*3*3);
        
        pVertexs[9] = 0.0f; pVertexs[10] = 1.0f; pVertexs[11] = 0.0f;
        pVertexs[12] = 1.0f; pVertexs[13] = 0.0f; pVertexs[14] = 0.0f;
        pVertexs[15] = 1.0f; pVertexs[16] = 1.0f; pVertexs[17] = 0.0f;
        pTexcoords[6] = 0.0f; pTexcoords[7] = 0.0f;
        pTexcoords[8] = 1.0f; pTexcoords[9] = 1.0f;
        pTexcoords[10] = 1.0f; pTexcoords[11] = 0.0f;
        ZeroMemory(pNormals+9, sizeof(float)*3*3);
        buffer->Unlock();
    }
    s_object->m_pVerBufferList.push_back(buffer);
}

void InitCg() {
    XELOG("init cg");
    CCg* p = NULL;
    CCgParam* param = NULL;
    
    //--------
    p = new CCg;
    p->Read(CCg::E_CgVertex, "test.vert");
    s_program->AddCg(p);
    
    param = new CCgParam("ModelViewProj");
    p->AddParam(param);
    
    //--------
    p = new CCg;
    p->Read(CCg::E_CgFragment, "test.frag");
    s_program->AddCg(p);
    
    CPass* pass = new CPass;
    CColorF color;
    pass->Init("logo-hd.pvr.ccz", true, color, color, color, color, "");
    
    param = new CCgParam("Samp0");
    param->SetPass(pass);
    p->AddParam(param);
    
    //--------
    s_program->Compile();
}

void Rotate() {
    static float s_R = 0;
//    s_R -= 0.01f;
//    if (s_R < 0) {
//        s_R = 1;
//    }
    s_camera->SetPosition(0,0,1);
}
