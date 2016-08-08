//
//  ViewController.h
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface ViewController : GLKViewController

@property (weak, nonatomic) IBOutlet UISlider *countSlider;
@property (weak, nonatomic) IBOutlet UISlider *triangleSlider;

@end
