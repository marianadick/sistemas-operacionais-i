#include "ship.h"

__BEGIN_API

Thread * Ship::_shipThread;

Ship::Ship()
{
    db<System>(TRC) << ">> Thread Ship is initializing...\n";
    _shipThread = new Thread(Ship::selectShipAnimation);
}

Ship::~Ship()
{
}

void Ship::join()
{
    if (_shipThread) {
        _shipThread->join();
        //_shipThread->yield();
    }
    else
        db<CPU>(ERR) << ">> Unnable to join Thread Ship.\n";
}

void Ship::selectShipAnimation() {
    std::cout << "SHIP ANIMATION" << std::endl; 
}

__END_API