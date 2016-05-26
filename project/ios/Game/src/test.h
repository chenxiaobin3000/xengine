//
//  test.hpp
//  Game
//
//  Created by chenxiaobin on 15/10/16.
//  Copyright © 2015年 xe. All rights reserved.
//

#ifndef test_h
#define test_h

typedef enum {
    E_XP,
    E_XS,
    E_YP,
    E_YS,
    E_ZP,
    E_ZS,
}   EMoveDir;

void InitTest(int width, int height);

void RenderTest();

void MoveTest(EMoveDir dir);

#endif /* test_h */
