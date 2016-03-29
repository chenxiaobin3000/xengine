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

#import "MyGUI.h"
#import "XeEngine.h"
#import "XeConfig.h"
#import "test.h"

#define kTextViewHeight 30 // 输入框高度

static XE::CEngine* ENGINE = nil;

@interface ViewController() <UITextViewDelegate> {
    BOOL bKeyboardShow;     // 是否显示键盘
    float fScale;           // 屏幕缩放比
}

@property (strong, nonatomic) EAGLContext* context;
@property (strong, nonatomic) UITextView* textView;
@property (strong, nonatomic) UITapGestureRecognizer* tap;      // 点击
@property (strong, nonatomic) UISwipeGestureRecognizer* swipe;  // 滑动
@property (strong, nonatomic) UIPanGestureRecognizer* pan;      // 拖拽

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    fScale = SCREEN_SCALE;
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;

    // 初始化gles
    [EAGLContext setCurrentContext:self.context];

    NSLog(@"game init\n");
    ENGINE = XE::CEngine::CSingleton::GetSingletonPtr();
    [self initGame];
    [self initTextView];
    [self initGestureRecognizer];
    
    InitTest(SCREEN_WIDTH*fScale, SCREEN_HEIGHT*fScale);
}

- (void)dealloc {
    NSLog(@"game quit\n");
    
    ENGINE->Free();

    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)initGame {
    XE::CConfig::SetScreenLandscape(true);
//    XE::CConfig::SetMouse2Touch(true);
    
    ENGINE->Init(SCREEN_WIDTH*fScale, SCREEN_HEIGHT*fScale);
}

- (void)initTextView {
    self.textView = [[UITextView alloc] init];
    self.textView.delegate = self;
    self.textView.font = [UIFont systemFontOfSize:16];
    self.textView.scrollEnabled = NO;
    
    self.textView.returnKeyType = UIReturnKeyDefault;
    self.textView.keyboardType = UIKeyboardTypeDefault;
    
    [self.view addSubview:self.textView];
    
    // 监听键盘消息
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardDidShow:)
                                                 name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardDidHide:)
                                                 name:UIKeyboardDidHideNotification object:nil];
}

- (void)initGestureRecognizer {
    self.tap = [[UITapGestureRecognizer alloc] init];
    self.swipe = [[UISwipeGestureRecognizer alloc] init];
    self.pan = [[UIPanGestureRecognizer alloc] init];
    
    [self.view addGestureRecognizer:self.tap];
    [self.view addGestureRecognizer:self.swipe];
    [self.view addGestureRecognizer:self.pan];
    
    [self.tap addTarget:self action:@selector(tapHandle:)];
    [self.swipe addTarget:self action:@selector(swipeHandle:)];
    [self.pan addTarget:self action:@selector(panHandle:)];
}

- (void)setIMEKeyboardState:(BOOL)show {
    if (show) {
        bKeyboardShow = YES;
        [self.textView becomeFirstResponder];
    } else {
        [self.textView resignFirstResponder];
        bKeyboardShow = NO;
    }
}

- (void)keyboardDidShow:(NSNotification *)notification {
    // 获取键盘位置
    NSValue *keyboardObject = [[notification userInfo] objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGRect keybaordRect;
    [keyboardObject getValue:&keybaordRect];
    
    // 设置输入框跟随键盘
    CGFloat y = self.view.frame.size.height-keybaordRect.size.height-kTextViewHeight;
    CGRect textViewRect = CGRectMake(0, y, self.view.frame.size.width, kTextViewHeight);
    [self.textView setFrame:textViewRect];
}

- (void)keyboardDidHide:(NSNotification *)notification {
    // 隐藏输入框
    CGFloat y = self.view.frame.size.height;
    CGRect textViewRect = CGRectMake(0, y, self.view.frame.size.width, kTextViewHeight);
    [self.textView setFrame:textViewRect];
}

- (void)tapHandle:(UITapGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
    MyGUI::InputManager::getInstance().injectMousePress(point.x*fScale, point.y*fScale, MyGUI::MouseButton::Left);
    MyGUI::InputManager::getInstance().injectMouseRelease(point.x*fScale, point.y*fScale, MyGUI::MouseButton::Left);
    NSLog(@"tap x: %.02f, y: %.02f", point.x*fScale, point.y*fScale);
}

- (void)swipeHandle:(UISwipeGestureRecognizer *)sender {
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
}

- (void)panHandle:(UIPanGestureRecognizer *)sender {
//    MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    //ENGINE->Render();
    RenderTest();
}

#pragma mark - Touch Delegate

// 任意点击关闭输入法
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    if (bKeyboardShow) {
        return;
    }
    [self setIMEKeyboardState:NO];
}

#pragma mark - TextView Delegate

- (void)textViewDidBeginEditing:(UITextView *)textView {
    textView.text = @"";
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView {
    return true;
}

- (void)textViewDidEndEditing:(UITextView *)textView {
//    const char* text = [textView.text UTF8String];
//    MyGUI::InputManager::getInstance().injectKeyPress(_key, _text);
//    MyGUI::InputManager::getInstance().injectKeyRelease(_key);
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    // 换行关闭输入法
    if ([text isEqualToString:@"\n"]) {
        [self setIMEKeyboardState:NO];
        return NO;
    }
    return YES;
}

@end
