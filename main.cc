/**
 * @file main.cc
 * @brief
 * 
 */
#include "header-files/thread.h"
#include "header-files/system.h"
#include "header-files/game.h"

__USING_API

int main(void)
{
   System::init(&Game::gameRun);
}