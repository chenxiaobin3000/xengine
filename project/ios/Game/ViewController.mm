//
//  ViewController.m
//  Game
//
//  Created by chenxiaobin on 15/10/16.
//  Copyright © 2015年 xe. All rights reserved.
//

#import "ViewController.h"

@interface ViewController () <UITextViewDelegate>

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

    //[self initTextView];
    [self initGame];
}

- (void)dealloc {
    NSLog(@"game quit\n");
//    if (s_pIOSNativeInterface) {
//        XI::DetachInterface();
//        delete s_pIOSNativeInterface;
//        s_pIOSNativeInterface = NULL;
//    }
//    
//    XCli::CApp::GetSingleton().Quit();
//    XCli::CApp::GetSingleton().Free();
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)initGame {
//    const char* szPath = XI::GetWritablePath();
//    if (szPath) {
//        XLOG("game init %s\n", szPath);
//    } else {
//        XLOG("game init err\n");
//        return;
//    }
//    
//#ifndef kScreenLandscape
//    XI::SetScreenWidth(self.view.bounds.size.width);
//    XI::SetScreenHeight(self.view.bounds.size.height);
//#else
//    XI::SetScreenWidth(self.view.bounds.size.height);
//    XI::SetScreenHeight(self.view.bounds.size.width);
//#endif //kScreenLandscape
//    XI::SetScreenScale([[UIScreen mainScreen] scale]);
//    
//    XCli::CApp::GetSingleton().Init();
//    
//    s_pIOSNativeInterface = new IOSNativeInterface;
//    if (s_pIOSNativeInterface) {
//        s_pIOSNativeInterface->Init(self);
//        XI::AttachInterface(s_pIOSNativeInterface);
//    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    //usleep(17000);
    //XCli::CApp::GetSingleton().Run();
}

- (NSUInteger)supportedInterfaceOrientations {
#ifndef kScreenLandscape
    return UIInterfaceOrientationMaskPortrait;
#else
    return UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
#endif //kScreenLandscape
}

@end
