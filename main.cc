/**
 * @file main.cc
 * @brief
 * 
 */

#include "header-files/system.h"
#include "header-files/game.h"
#include "header-files/thread.h"

__USING_API

int main(void)
{
   System::init(&Game::gameRun);
}