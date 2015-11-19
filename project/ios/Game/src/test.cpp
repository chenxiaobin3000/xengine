//
//  test.cpp
//  Game
//
//  Created by chenxiaobin on 15/10/16.
//  Copyright © 2015年 xe. All rights reserved.
//

#include "test.h"

void MakeCube() {
    
}

void InitTest() {
    MakeCube();
}

void RenderTest() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
   	glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
}
