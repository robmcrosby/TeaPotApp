//
//  StringUtils.m
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#import "StringUtils.h"
#import <Foundation/Foundation.h>

using namespace std;

std::string StringUtils::ReadTextFile(const std::string &filename) {
  NSString *filePath = [[NSBundle mainBundle] pathForResource:@"basic" ofType:@"vert"];
  
  NSError *error = nil;
  NSString *contents = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:&error];
  if (contents == nil)
  {
    NSLog(@"%@", error);
    return "";
  }
  return string([contents UTF8String]);
}
