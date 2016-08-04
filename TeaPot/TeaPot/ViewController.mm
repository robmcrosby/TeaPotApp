//
//  ViewController.m
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>

@interface ViewController () {}
@property (strong, nonatomic) EAGLContext *context;
@end



@implementation ViewController


- (void)viewDidLoad
{
  // Application Starting
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
  //[self setupGL];
}


- (void)dealloc
{
  // Application Closing
  //[self tearDownGL];
  if ([EAGLContext currentContext] == self.context) {
    [EAGLContext setCurrentContext:nil];
  }
}


- (void)didReceiveMemoryWarning
{
  [super didReceiveMemoryWarning];
  
  if ([self isViewLoaded] && ([[self view] window] == nil)) {
    self.view = nil;
    //[self tearDownGL];
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


- (void)update
{
  // Update the Application
  //self.timeSinceLastUpdate
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
  // Render OpenGL
  glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




@end
