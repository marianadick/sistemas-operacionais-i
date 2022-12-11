#include "header-files/game.h"

__BEGIN_API

Thread * Game::_shipThread;
Thread * Game::_windowThread;
Thread * Game::_kbThread;
Thread * Game::_collisionThread;
Thread * Game::_enemyGroupPurpleThread;

Ship * Game::_ship;
Window * Game::_window;
Input * Game::_kb;
Collision * Game::_collision;
EnemyGroupPurple * Game::_enemyGroupPurple;


__END_API
