#include "window.h"

__BEGIN_API

Thread * Window::_windowThread;

Window::Window()
{
    db<System>(TRC) << ">> Thread Window is initializing...\n";
    _windowThread = new Thread(drawWindow);
}

Window::~Window()
{
}

void Window::join()
{
    if (_windowThread)
        _windowThread->join();
    else
        db<CPU>(ERR) << ">> Unnable to join Thread Window.\n";
}

void Window::drawWindow()
{

}

__END_API