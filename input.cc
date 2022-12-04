#include "input.h"

__BEGIN_API

Thread * Input::_inputThread;

Input::Input()
{
    _inputThread = new Thread(Input::getKey);
}

Input::~Input()
{
}

void Input::join()
{
    if (_inputThread)
        _inputThread->join();
}

void Input::getKey()
{
    std::cout << "GETTING KEY" << std::endl;
}

__END_API