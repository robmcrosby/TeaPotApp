//
//  Application.hpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <iostream>


/**
 * Singleton that controls the high level logic of the Application.
 */
class Application {
  
private:
  Application() {}
  Application(const Application&) {}
  ~Application() {}
  Application& operator=(const Application&) {return *this;}
  
public:
  static Application& instance();
  
  void setup();
  void teardown();
  
  void update(float time);
  void render();
};


#endif /* Application_hpp */
