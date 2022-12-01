/**
 * @file main.cc
 * @brief
 * 
 */


#include "Engine.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#include "thread.h"
#include "system.h"
#include "main_class.h"

__USING_API

int main() {
   srand(time(0));
   Engine shooty(800, 600, 60);
   shooty.init();
   shooty.run();

   //System::init(&MainClass::runGame);

   return 0;

}


