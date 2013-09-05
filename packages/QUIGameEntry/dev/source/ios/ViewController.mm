//
//  ViewController.m
//  TestOpenGL
//
//  Created by Cristian Bidea on 2/28/13.
//  Copyright (c) 2013 Cristian Bidea. All rights reserved.
//

#import "ViewController.h"
#import <qui/StandardGameEntry.h>
#import <QuartzCore/QuartzCore.h>
#import <qui/VirtualFS.h>
#import <qui/Timer.h>
#import <qui/log.h>
#import <qui/InputInterface.h>
#import <qui/TouchInputEvent.h>
#import <stdint.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

@interface ViewController () {
    qui::Timer timer;
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

    NSString* pathToBundle = [[NSBundle mainBundle] resourcePath];
	const char* pathToBundle_cstr = [pathToBundle UTF8String];
    qui::VirtualFS fs;
    fs.addRelativePath(pathToBundle_cstr);
    
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
    
    qui::game->getWindow().setSize(glm::vec2(ww, wh));
    qui::game->init();
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    [self setupGameWindow:self.interfaceOrientation];
}

- (void)tearDownGL
{
    qui::game->cleanup();
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
    qui::input::InputInterface ii;
    uint8_t count = [touches count];
    CGPoint location;
    for (uint8_t i = 0; i < count; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        location = [touch locationInView:self.view];
        location = [self adjustRetinaPoint:location];
        ii.addTouchEvent(new qui::input::TouchInputEvent(qui::input::TouchInputEvent::DOWN, (uint32_t)touch, location.x, location.y));
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    qui::input::InputInterface ii;
    uint8_t count = [touches count];
    CGPoint location;
    for (uint8_t i = 0; i < count; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        location = [touch locationInView:self.view];
        location = [self adjustRetinaPoint:location];
        ii.addTouchEvent(new qui::input::TouchInputEvent(qui::input::TouchInputEvent::UP, (uint32_t)touch, location.x, location.y));
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    qui::input::InputInterface ii;
    uint8_t count = [touches count];
    CGPoint location;
    for (uint8_t i = 0; i < count; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        location = [touch locationInView:self.view];
        location = [self adjustRetinaPoint:location];
        ii.addTouchEvent(new qui::input::TouchInputEvent(qui::input::TouchInputEvent::UP, (uint32_t)touch, location.x, location.y));
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    qui::input::InputInterface ii;
    uint8_t count = [touches count];
    CGPoint location;
    for (uint8_t i = 0; i < count; i++)
    {
        UITouch *touch = [[touches allObjects] objectAtIndex:i];
        location = [touch locationInView:self.view];
        location = [self adjustRetinaPoint:location];
        ii.addTouchEvent(new qui::input::TouchInputEvent(qui::input::TouchInputEvent::MOVE, (uint32_t)touch, location.x, location.y));
    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    qui::input::InputInterface ii;
    ii.fireUpdateListeners();
    qui::game->update(timer.getDeltaTime());
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qui::game->paint();
}

@end
