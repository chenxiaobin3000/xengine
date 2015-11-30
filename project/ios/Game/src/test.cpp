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

using namespace XE;

static CVertexBuffer* s_buffer = NULL;
static CCgProgram* s_program = NULL;

void MakeCube() {
    float* pVertexs;
    float* pTexcoords;
    float* pNormals;
    unsigned int* pIndexs;
    s_buffer->SetCount(3, 0);
    if (s_buffer->Lock(pVertexs, pTexcoords, pNormals, pIndexs)) {
        pVertexs[0] = 0.0f; pVertexs[1] = 0.0f; pVertexs[2] = 0.0f;
        pVertexs[3] = 0.0f; pVertexs[4] = 1.0f; pVertexs[5] = 0.0f;
        pVertexs[6] = 1.0f; pVertexs[7] = 1.0f; pVertexs[8] = 0.0f;
    }
}

void InitCg() {
    CCg* p = new CCg;
    p->Read(CCg::E_CgVertex, "testVertex.glsl");
    s_program->AddCg(p);
    
    p = new CCg;
    p->Read(CCg::E_CgFragment, "testFragment.glsl");
    s_program->AddCg(p);
    
    s_program->Compile();
}

void InitTest() {
	//static CRenderScene CRenderScene;
	//static CCamera camera;
	//scene.Render(camera);

    s_buffer = new CVertexBuffer();
    s_program = new CCgProgram();
    
    MakeCube();
    InitCg();
}

void RenderTest() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   	glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    
    s_program->Bind(NULL);
    s_buffer->Render();
    s_program->UnBind();
}
