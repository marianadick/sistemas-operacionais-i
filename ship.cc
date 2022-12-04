#include "ship.h"

__BEGIN_API

Thread * Ship::_shipThread;

Ship::Ship()
{
    _shipThread = new Thread(Ship::selectShipAnimation);
}

Ship::~Ship()
{
}

void Ship::join()
{
    if (_shipThread)
        _shipThread->join();
}

void Ship::selectShipAnimation() {
    std::cout << "SHIP ANIMATION" << std::endl; 
}

__END_API