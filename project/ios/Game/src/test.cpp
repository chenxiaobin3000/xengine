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

using namespace XE;

static CVertexBuffer* s_buffer = NULL;
static CCgProgram* s_program = NULL;

void MakeCube() {
    XELOG("make cube");
    float* pVertexs;
    float* pTexcoords;
    float* pNormals;
    unsigned int* pIndexs;
    s_buffer->SetCount(6, 0);
    if (s_buffer->Lock(pVertexs, pTexcoords, pNormals, pIndexs)) {
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
        s_buffer->Unlock();
    }
}

void InitCg() {
    XELOG("init cg");
    CCg* p = new CCg;
    p->Read(CCg::E_CgVertex, "test.vert");
    s_program->AddCg(p);
    
    p = new CCg;
    p->Read(CCg::E_CgFragment, "test.frag");
    s_program->AddCg(p);
    
    CPass* pass = new CPass;
    CColorF color;
    pass->Init("logo-hd.pvr.ccz", true, color, color, color, color, "");
    
    CCgParam* param = new CCgParam("Samp0");
    param->SetPass(pass);
    p->AddParam(param);
    
    s_program->Compile();
}

void InitTest() {
    XELOG("init test");
	//static CRenderScene CRenderScene;
	//static CCamera camera;
	//scene.Render(camera);

    s_buffer = new CVertexBuffer;
    s_program = new CCgProgram;
    
    MakeCube();
    InitCg();
}

void InitLook() {
//    GLfloat projection[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
//
//    float ymax, xmax;
//    ymax = info.fViewNear * tanf(45.0f * PI / 360.0f);
//    xmax = ymax * info.fScreenWidth/info.fScreenHeight;
//    glhOrtho(projection, -xmax, xmax, -ymax, ymax, info.fViewNear, info.fViewFar);
}

void RenderTest() {
    glViewport(0, 0, (GLsizei)640, (GLsizei)480);
    
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   	glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    
    InitLook();
    
    s_program->Bind(NULL);
    s_buffer->Render();
    s_program->UnBind();
}
