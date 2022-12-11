#include "header-files/game.h"

__BEGIN_API

Thread * Game::_shipThread;
Thread * Game::_windowThread;
Thread * Game::_kbThread;

Ship * Game::_ship;
Window * Game::_window;
Input * Game::_kb;

EnemyGroupPurple *Game::_enemyGroupPurple;

__END_API
