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
#include "../../../../engine/XeRenderScene.h"

#include "../../../../deps/mygui/MyGUIEngine/include/MyGUI.h"
#include "../../../../engine/MyGUI/MyPlatform.h"

using namespace XE;

static int s_width = 0;
static int s_height = 0;

static std::vector<CPass*> s_passList;
static CCgProgram* s_program = NULL;
static std::vector<CRenderObject*> s_objList;
static CCamera* s_camera = NULL;
static CRenderScene* s_scene = NULL;

void MakeCube(CRenderObject* obj, float x, float y, float z);
void InitCg();
void InitMyGUI();
void Rotate();

void InitTest(int width, int height) {
    XELOG("init test");
    s_width = width;
    s_height = height;
    
	//static CCamera camera;
	//scene.Render(camera);

    s_program = new CCgProgram;
    
	CRenderObject* object1 = new CRenderObject;
    MakeCube(object1, -0.3f, 0.0f, 0.0f);
    s_objList.push_back(object1);
    
    CRenderObject* object2 = new CRenderObject;
    MakeCube(object2, 0.3f, 0.0f, 0.0f);
    s_objList.push_back(object2);

	CVertex f(0,0,-1);
	CPoint s(s_width,s_height);
	s_camera = new CCamera(f, s, 10, 500);
    s_camera->SetPosition(0, 0, 1);
    
    s_scene = new CRenderScene;
    
    InitCg();
    InitMyGUI();
}

void RenderTest() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);

    glViewport(0, 0, (GLsizei)s_width, (GLsizei)s_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Rotate();
	s_camera->Lookat();

	// -- render object --
    auto ite = s_objList.begin();
    auto end = s_objList.end();
    for (; end!=ite; ++ite) {
        (*ite)->Render(s_camera);
	}
	
	// -- render buffer --
    for (int i=0; i<2; ++i) {
        s_program->SetPass(s_passList[i]);
        s_program->Bind(s_scene);
    
        //ite = s_objList.begin();
        //for (; end!=ite; ++ite) {
            s_program->SetTarget(s_objList[i]);
            s_objList[i]->Draw();
        //}
        s_program->UnBind();
    }
    
    MyGUI::MyRenderManager* pMgr = MyGUI::MyRenderManager::getInstancePtr();
    if (pMgr) {
        pMgr->setViewSize(s_width, s_height);
        pMgr->drawOneFrame();
    }
}

void MakeCube(CRenderObject* obj, float x, float y, float z) {
    XELOG("make cube");
    float* pVertexs;
    float* pTexcoords;
    float* pNormals;
    unsigned int* pIndexs;
    CVertexBuffer* buffer = new CVertexBuffer;
    buffer->SetCount(6, 0);
    float boxs = 0.5f;
    if (buffer->Lock(pVertexs, pTexcoords, pNormals, pIndexs)) {
        pVertexs[0] = 0.0f+x; pVertexs[1] = 0.0f+y; pVertexs[2] = 0.0f+z;
        pVertexs[3] = 0.0f+x; pVertexs[4] = boxs+y; pVertexs[5] = 0.0f+z;
        pVertexs[6] = boxs+x; pVertexs[7] = 0.0f+y; pVertexs[8] = 0.0f+z;
        pTexcoords[0] = 0.0f; pTexcoords[1] = 1.0f;
        pTexcoords[2] = 0.0f; pTexcoords[3] = 0.0f;
        pTexcoords[4] = 1.0f; pTexcoords[5] = 1.0f;
        ZeroMemory(pNormals, sizeof(float)*3*3);
        
        pVertexs[9]  = 0.0f+x; pVertexs[10] = boxs+y; pVertexs[11] = 0.0f+z;
        pVertexs[12] = boxs+x; pVertexs[13] = 0.0f+y; pVertexs[14] = 0.0f+z;
        pVertexs[15] = boxs+x; pVertexs[16] = boxs+y; pVertexs[17] = 0.0f+z;
        pTexcoords[6] = 0.0f; pTexcoords[7] = 0.0f;
        pTexcoords[8] = 1.0f; pTexcoords[9] = 1.0f;
        pTexcoords[10] = 1.0f; pTexcoords[11] = 0.0f;
        ZeroMemory(pNormals+9, sizeof(float)*3*3);
        buffer->Unlock();
    }
    obj->m_pVerBufferList.push_back(buffer);
}

void InitCg() {
    XELOG("init cg");
    
    CTexture* pTexture = XENEW(CTexture);
    if (!pTexture) {
        return;
    }
    if (!pTexture->Load("logo.pvr.ccz")) {
        return;
    }
    
    CColorF color;
    CPass* pass1 = new CPass;
    pass1->Init(pTexture, true, color, color, color, color, "");
    s_passList.push_back(pass1);
    
        
    pTexture = XENEW(CTexture);
    if (!pTexture) {
        return;
    }
    if (!pTexture->Load("HelpIcon.pvr.ccz")) {
        return;
    }

    CPass* pass2 = new CPass;
    pass2->Init(pTexture, true, color, color, color, color, "");
    s_passList.push_back(pass2);
    
    //--------
    CCg* p = NULL;
    CCgParam* param = NULL;
    CCgParam* paramSamp0 = NULL;
    
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
    
    paramSamp0 = new CCgParam("Samp0");
    p->AddParam(paramSamp0);
    
    //--------
    s_program->Compile();
}

void InitMyGUI() {
    MyGUI::PointerManager::getInstance().setVisible(false);
    
    const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
    if (root.size() == 1) {
        root.at(0)->findWidget("Text")->castType<MyGUI::EditBox>()->setCaption("Sample colour picker implementation");
    }
  
//    MyGUI::EditBox* edit = MyGUI::Gui::getInstance().createWidget<MyGUI::EditBox>("EditBoxStretch", MyGUI::IntCoord(10, 80, 600, 600), MyGUI::Align::Default, "Overlapped");
//    edit->setCaption("some edit");
//    edit->setTextAlign(MyGUI::Align::Center);
//    edit->setEditMultiLine(true);
//    edit->setFontHeight(80);
    
//    class ButtonDelegate {
//    public:
//        void mousePressed(MyGUI::Widget* _widget) {
//            printf("click\n");
//        }
//    };
//
//    MyGUI::ButtonPtr button = root.at(0)->createWidget<MyGUI::Button>("Button",10,40,300,80,MyGUI::Align::Default,"Overlapped");
//    button->setCaption("exit");
//    button->setFontHeight(80);
//    ButtonDelegate* delegate = new ButtonDelegate;
//    button->eventMouseButtonClick += MyGUI::newDelegate(delegate, &ButtonDelegate::mousePressed);
}

void Rotate() {
    static float s_R = 0;
//    s_R -= 0.01f;
//    if (s_R < 0) {
//        s_R = 1;
//    }
    s_camera->SetPosition(0,0,1);
}
