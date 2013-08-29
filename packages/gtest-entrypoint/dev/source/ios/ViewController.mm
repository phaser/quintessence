//
//  ViewController.m
//  TestOpenGL
//
//  Created by Cristian Bidea on 2/28/13.
//  Copyright (c) 2013 Cristian Bidea. All rights reserved.
//

#import "ViewController.h"
#import <QuartzCore/QuartzCore.h>
#import <qui/Timer.h>
#import <qui/log.h>
#import <stdint.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

@interface ViewController () {
    bool retina;
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;
- (void)setupGameWindow:(UIInterfaceOrientation)toIfaceOrient;
- (BOOL)loadShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;
- (CGPoint)adjustRetinaPoint:(CGPoint)location;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    if ([[UIScreen mainScreen] respondsToSelector:@selector(displayLinkWithTarget:selector:)] &&
        ([UIScreen mainScreen].scale == 2.0)) {
        LOG(INFO) << "Running on a retina device!";
        retina = true;
    } else {
        retina = false;
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.layer.contentsScale = view.contentScaleFactor = retina ? 2 : 1;
    [view setNeedsLayout];

    [self setupGL];
}

- (void)dealloc
{
    [super dealloc];
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}
- (void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)toIfaceOrient
                                 duration:(NSTimeInterval)duration
{
    [self setupGameWindow:toIfaceOrient];
}

- (void)setupGameWindow:(UIInterfaceOrientation)toIfaceOrient
{
    uint16_t ww, wh;
    if (retina)
    {
        ww = [UIScreen mainScreen].currentMode.size.width;
        wh = [UIScreen mainScreen].currentMode.size.height;
    }
    else
    {
        CGRect screenRect = [[UIScreen mainScreen] bounds];
        ww = screenRect.size.width;
        wh = screenRect.size.height;
    }
    
    if (UIInterfaceOrientationIsLandscape(toIfaceOrient))
    {
        uint16_t wb = ww;
        ww = wh;
        wh = wb;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    [self setupGameWindow:self.interfaceOrientation];
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

- (CGPoint)adjustRetinaPoint:(CGPoint)location
{
    CGPoint result = location;
    if (retina)
    {
        result.x *= 2;
        result.y *= 2;
    }
    return result;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

@end
