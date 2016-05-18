//
//  test.cpp
//  Game
//
//  Created by chenxiaobin on 15/10/16.
//  Copyright © 2015年 xe. All rights reserved.
//

#include "test.h"
#include "stdafx.h"
#include "XeVertexBuffer.h"
#include "XeCgProgram.h"
#include "XePass.h"
#include "XeCamera.h"
#include "XeRenderScene.h"
#include "XeMaterialLoader.h"
#include "XeRenderObjectLoader.h"
#include "XeSkinRenderObjectLoader.h"
#include "XeSkeletonLoader.h"

#include "MyGUI.h"
#include "MyPlatform.h"

using namespace XE;

static int s_width = 0;
static int s_height = 0;

static CMaterial* s_pMaterial;
static std::vector<CRenderObject*> s_objList;
static CCamera* s_camera = NULL;
static CRenderScene* s_scene = NULL;

void MakeCube(CRenderObject* obj, float x, float y, float z);
void InitMaterial();
void InitMyGUI();
void Rotate();

void InitTest(int width, int height) {
    XELOG("init test");
    s_width = width;
    s_height = height;
    
	//static CCamera camera;
	//scene.Render(camera);

    CRenderObject* object1 = new CRenderObject;
    MakeCube(object1, -0.3f, 0.0f, 0.0f);
    s_objList.push_back(object1);
    
    CRenderObject* object2 = new CRenderObject;
    MakeCube(object2, 0.3f, 0.0f, 0.0f);
    s_objList.push_back(object2);

//    CRenderObject* object3 = CRenderObjectLoader::Load("man_arm.l.mesh.xml");
//    s_objList.push_back(object3);
    
	CVertex f(0,0,-1);
	CPoint s(s_width,s_height);
	s_camera = new CCamera(f, s, 10, 500);
    s_camera->SetPosition(0, 0, 1);
    
    s_scene = new CRenderScene;
    
    InitMaterial();
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
        s_pMaterial->Bind(s_scene);
    
        //ite = s_objList.begin();
        //for (; end!=ite; ++ite) {
            s_pMaterial->SetTarget(s_objList[i]);
            s_objList[i]->Draw();
        //}
        s_pMaterial->UnBind();
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
    obj->m_pVertexBuffer = new CVertexBuffer;
    obj->m_pVertexBuffer->SetVertexCount(6);
    //obj->m_pVertexBuffer->SetIndexCount(0);
    float boxs = 0.5f;
    if (obj->m_pVertexBuffer->Lock(pVertexs, pTexcoords, pNormals, pIndexs)) {
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
        obj->m_pVertexBuffer->Unlock();
    }
}

void InitMaterial() {
    XELOG("init material");
    s_pMaterial = CMaterialLoader::Load("light.material");
    
    CTexture* pTexture = XENEW(CTexture);
    if (!pTexture) {
        return;
    }
    if (!pTexture->Load("HelpIcon.pvr.ccz")) {
        return;
    }

    s_objList[1]->SetTexture(pTexture);
}

void InitMyGUI() {
    MyGUI::PointerManager::getInstance().setVisible(false);
    
    const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
    if (root.size() == 1) {
        root.at(0)->findWidget("Text")->castType<MyGUI::EditBox>()->setCaption("Sample colour picker implementation");
    }
    
    MyGUI::EditBox* edit = MyGUI::Gui::getInstance().createWidget<MyGUI::EditBox>("EditBoxStretch", MyGUI::IntCoord(10, 80, 600, 600), MyGUI::Align::Default, "Overlapped");
    edit->setCaption("some edit");
    edit->setTextAlign(MyGUI::Align::Center);
    edit->setEditMultiLine(true);
    edit->setFontHeight(80);
//
//  ------------------------------------------
//    class ButtonDelegate {
//    public:
//        void mousePressed(MyGUI::Widget* _widget) {
//            printf("click\n");
//        }
//    };
//
//    MyGUI::ButtonPtr button = MyGUI::Gui::getInstance().createWidget<MyGUI::Button>("Button",10,40,300,80,MyGUI::Align::Default,"Overlapped");
//    button->setCaption("exit");
//    button->setFontHeight(80);
//    ButtonDelegate* delegate = new ButtonDelegate;
//    button->eventMouseButtonClick += MyGUI::newDelegate(delegate, &ButtonDelegate::mousePressed);
}

void Rotate() {
//    static float s_R = 0;
//    s_R -= 0.01f;
//    if (s_R < 0) {
//        s_R = 1;
//    }
    s_camera->SetPosition(0,0,1);
}
