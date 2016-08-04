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

@interface ViewController () {}
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
  Application::instance().setup();
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


@end
