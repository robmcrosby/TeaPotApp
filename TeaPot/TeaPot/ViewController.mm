//
//  ViewController.m
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>

#import "Application.h"
#import <CoreMotion/CoreMotion.h>

@interface ViewController () {
  CMMotionManager *mMotionManager;
}
@property (strong, nonatomic) EAGLContext *context;
@end



@implementation ViewController


// Application Starting
- (void)viewDidLoad
{
  [super viewDidLoad];
  
  // Get an OpenGL ES 2.0 Context
  self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
  if (!self.context) {
    NSLog(@"Failed to create ES context");
  }
  
  // Setup the OpenGL View and Depth Buffer
  GLKView *view = (GLKView *)self.view;
  view.context = self.context;
  view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
  
  [EAGLContext setCurrentContext:self.context];
  
  float width = (float)view.frame.size.width;
  float height = (float)view.frame.size.height;
  Application::instance().setup(width, height);
  
  [self setupMotion];
}

// Change of Device Rotation
- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
  float width = (float)size.width;
  float height = (float)size.height;
  Application::instance().resize(width, height);
}


// Application Closing
- (void)dealloc
{
  Application::instance().teardown();
  if ([EAGLContext currentContext] == self.context) {
    [EAGLContext setCurrentContext:nil];
  }
}


- (void)didReceiveMemoryWarning
{
  [super didReceiveMemoryWarning];
  
  if ([self isViewLoaded] && ([[self view] window] == nil)) {
    self.view = nil;
    Application::instance().teardown();
    if ([EAGLContext currentContext] == self.context) {
      [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
  }
}


// Hide the Status Bar
- (BOOL)prefersStatusBarHidden {
  return YES;
}


// Update the Application
- (void)update
{
  Application::instance().update((float)self.timeSinceLastUpdate);
}


// Render an OpenGL Frame
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
  Application::instance().render();
}


- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
  UITouch *touch = [touches anyObject];
  CGPoint position = [touch locationInView:self.view];
  Application::instance().touchDown((float)position.x, (float)position.y);
}

- (void)handleMotion: (CMDeviceMotion *)motion
{
  CMQuaternion quat = motion.attitude.quaternion;
  Application::instance().handleMotion((float)quat.x,
                                       (float)quat.y,
                                       (float)quat.z,
                                       (float)quat.w);
}

- (void)setupMotion
{
  mMotionManager = [[CMMotionManager alloc] init];
  if (mMotionManager.deviceMotionAvailable) {
    mMotionManager.deviceMotionUpdateInterval = 1.0/60.0;
    [mMotionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue currentQueue]
                                        withHandler:^(CMDeviceMotion *motion, NSError *error) {
                                          [self handleMotion: motion];
                                        }];
  }
}

@end
