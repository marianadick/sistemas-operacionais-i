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

   System::init(&MainClass::runGame);

   return 0;

}


