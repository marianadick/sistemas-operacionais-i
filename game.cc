#include "header-files/game.h"

__BEGIN_API

Thread * Game::_shipThread;
Thread * Game::_windowThread;
Thread * Game::_kbThread;
Thread * Game::_collisionThread;
Thread * Game::_enemyGroupPurpleThread;
Thread * Game::_enemyGroupWhiteThread;
Thread * Game::_MinesControlThread;


Ship * Game::_ship;
Window * Game::_window;
Input * Game::_kb;
CollisionHandler * Game::_collision;
PurpleCreepLauncher * Game::_enemyGroupPurple;
WhiteCreepLauncher * Game::_enemyGroupWhite;
MinesControl * Game::_MinesControl;


__END_API
