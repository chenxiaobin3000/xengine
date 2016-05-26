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
    BOOL bKeyboardShow;             // 是否显示键盘
    float fScreenScale;             // 屏幕缩放比
    CGPoint fPanPoint;              // 拖拽位置
    float fPinchScale;              // 手势缩放
}

@property (strong, nonatomic) EAGLContext* context;
@property (strong, nonatomic) UITextView* textView;
@property (strong, nonatomic) UITapGestureRecognizer* signleTap;        // 单击
@property (strong, nonatomic) UITapGestureRecognizer* doubleTap;        // 双击
@property (strong, nonatomic) UISwipeGestureRecognizer* leftSwipe;      // 左滑动
@property (strong, nonatomic) UISwipeGestureRecognizer* rightSwipe;     // 右滑动
@property (strong, nonatomic) UISwipeGestureRecognizer* upSwipe;        // 上滑动
@property (strong, nonatomic) UISwipeGestureRecognizer* downSwipe;      // 下滑动
@property (strong, nonatomic) UIPanGestureRecognizer* pan;              // 拖拽
@property (strong, nonatomic) UIPinchGestureRecognizer* pinch;          // 捏合

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    fScreenScale = SCREEN_SCALE;
    fPanPoint = CGPointMake(0, 0);
    fPinchScale = 1.0f;
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
    
    InitTest(SCREEN_WIDTH*fScreenScale, SCREEN_HEIGHT*fScreenScale);
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
    
    ENGINE->Init(SCREEN_WIDTH*fScreenScale, SCREEN_HEIGHT*fScreenScale);
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
    self.signleTap = [[UITapGestureRecognizer alloc] init];
    self.signleTap.numberOfTapsRequired = 1;
    [self.view addGestureRecognizer:self.signleTap];
    [self.signleTap addTarget:self action:@selector(singleTapHandle:)];
    
    self.doubleTap = [[UITapGestureRecognizer alloc] init];
    self.doubleTap.numberOfTapsRequired = 2;
    [self.view addGestureRecognizer:self.doubleTap];
    [self.doubleTap addTarget:self action:@selector(doubleTapHandle:)];
    [self.signleTap requireGestureRecognizerToFail:self.doubleTap];
    
//    self.leftSwipe = [[UISwipeGestureRecognizer alloc] init];
//    self.leftSwipe.direction = UISwipeGestureRecognizerDirectionLeft;
//    [self.view addGestureRecognizer:self.leftSwipe];
//    [self.leftSwipe addTarget:self action:@selector(leftSwipeHandle:)];
//    
//    self.rightSwipe = [[UISwipeGestureRecognizer alloc] init];
//    self.rightSwipe.direction = UISwipeGestureRecognizerDirectionRight;
//    [self.view addGestureRecognizer:self.rightSwipe];
//    [self.rightSwipe addTarget:self action:@selector(rightSwipeHandle:)];
//    
//    self.upSwipe = [[UISwipeGestureRecognizer alloc] init];
//    self.upSwipe.direction = UISwipeGestureRecognizerDirectionUp;
//    [self.view addGestureRecognizer:self.upSwipe];
//    [self.upSwipe addTarget:self action:@selector(upSwipeHandle:)];
//    
//    self.downSwipe = [[UISwipeGestureRecognizer alloc] init];
//    self.downSwipe.direction = UISwipeGestureRecognizerDirectionDown;
//    [self.view addGestureRecognizer:self.downSwipe];
//    [self.downSwipe addTarget:self action:@selector(downSwipeHandle:)];
    
    self.pan = [[UIPanGestureRecognizer alloc] init];
    [self.view addGestureRecognizer:self.pan];
    [self.pan addTarget:self action:@selector(panHandle:)];
//    [self.pan requireGestureRecognizerToFail:self.leftSwipe];
//    [self.pan requireGestureRecognizerToFail:self.rightSwipe];
//    [self.pan requireGestureRecognizerToFail:self.upSwipe];
//    [self.pan requireGestureRecognizerToFail:self.downSwipe];
    
    self.pinch = [[UIPinchGestureRecognizer alloc] init];
    [self.view addGestureRecognizer:self.pinch];
    [self.pinch addTarget:self action:@selector(pinchHandle:)];
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

- (void)singleTapHandle:(UITapGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
    MyGUI::InputManager::getInstance().injectMousePress(point.x*fScreenScale, point.y*fScreenScale, MyGUI::MouseButton::Left);
    MyGUI::InputManager::getInstance().injectMouseRelease(point.x*fScreenScale, point.y*fScreenScale, MyGUI::MouseButton::Left);
    NSLog(@"tap x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)doubleTapHandle:(UITapGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
    NSLog(@"tap2 x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)leftSwipeHandle:(UISwipeGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MoveTest(E_XP);
    NSLog(@"swipe left x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)rightSwipeHandle:(UISwipeGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MoveTest(E_XS);
    NSLog(@"swipe right x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)upSwipeHandle:(UISwipeGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MoveTest(E_YP);
    NSLog(@"swipe up x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)downSwipeHandle:(UISwipeGestureRecognizer *)sender {
    CGPoint point = [sender locationInView:self.view];
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MoveTest(E_YS);
    NSLog(@"swipe down x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)panHandle:(UIPanGestureRecognizer *)sender {
    if (UIGestureRecognizerStateBegan == [sender state]) {
        fPanPoint = [sender locationInView:self.view];
        return;
    }
    
    CGPoint point = [sender locationInView:self.view];
    float x = fPanPoint.x - point.x;
    float y = fPanPoint.y - point.y;
    if (x > 1.0f) {
        MoveTest(E_XP);
    } else if (x < -1.0f) {
        MoveTest(E_XS);
    }
    
    if (y > 1.0f) {
        MoveTest(E_YP);
    } else if (y < -1.0f) {
        MoveTest(E_YS);
    }
    fPanPoint = point;
    
//    MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
    NSLog(@"pan x: %.02f, y: %.02f", point.x*fScreenScale, point.y*fScreenScale);
}

- (void)pinchHandle:(UIPinchGestureRecognizer *)sender {
    if(UIGestureRecognizerStateEnded == [sender state]) {
        fPinchScale = 1.0f;
        return;
    }
    
    float originalScale = [sender scale];
    float scale = 1.0f - (fPinchScale - originalScale);

    fPinchScale = originalScale;
    
    if (scale > 1.0f) {
        MoveTest(E_ZP);
    } else {
        MoveTest(E_ZS);
    }
    
//    MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
//    MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
//    MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
    NSLog(@"pinch scale: %.02f", scale);
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
