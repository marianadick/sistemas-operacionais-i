#include "input.h"

__BEGIN_API

Thread * Input::_inputThread;

Input::Input()
{
    db<System>(TRC) << ">> Thread Input is initializing...\n";
    _inputThread = new Thread(Input::getKey);
}

Input::~Input()
{
}

void Input::join()
{
    if (_inputThread)
        _inputThread->join();
    else
        db<CPU>(ERR) << ">> Unnable to join Thread Input.\n";
}

void Input::getKey()
{
    //al_get_keyboard_state(&kb);
    std::cout << "GETTING KEY" << std::endl;
}

__END_API