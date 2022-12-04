#include "window.h"

__BEGIN_API

Thread * Window::_windowThread;

Window::Window()
{
    _windowThread = new Thread(Window::drawWindow);
}

Window::~Window()
{
    // TODO
}

void Window::drawWindow()
{
    // TODO
}


__END_API