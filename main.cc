/**
 * @file main.cc
 * @brief
 * 
 */


#include "header-files/Engine.h"
#include <allegro5/allegro.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#include "header-files/thread.h"
#include "header-files/system.h"
#include "header-files/main_class.h"

__USING_API

int main() {

   System::init(&MainClass::runGame);

   return 0;

}


