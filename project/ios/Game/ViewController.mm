//
//  ViewController.m
//  Game
//
//  Created by chenxiaobin on 15/10/16.
//  Copyright © 2015年 xe. All rights reserved.
//

#import "stdafx.h"
#import "ViewController.h"
#import "CommonFunction.h"

#import "XeEngine.h"
#import "XeConfig.h"
#import "test.h"

static XE::CEngine* ENGINE = nil;

@interface ViewController ()

@property (strong, nonatomic) EAGLContext *context;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    // 初始化gles
    [EAGLContext setCurrentContext:self.context];

    ENGINE = XE::CEngine::CSingleton::GetSingletonPtr();
    [self initGame];
    
    InitTest();
}

- (void)dealloc {
    NSLog(@"game quit\n");
    
    ENGINE->Free();

    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)initGame {
    NSString* path = [CommonFunction getWritePath];
    std::string strPath = [path UTF8String];
    strPath.append("/");
    
    ENGINE->Init(strPath.c_str());
}

#pragma mark - UIViewController

- (NSUInteger)supportedInterfaceOrientations {
    bool b = XE::CConfig::GetScreenLandscape();
    if (b) {
        return UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
    } else {
        return UIInterfaceOrientationMaskPortrait;
    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    ENGINE->Render();
    RenderTest();
}

@end
