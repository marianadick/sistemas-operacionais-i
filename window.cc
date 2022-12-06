#include "window.h"

__BEGIN_API

Thread * Window::_windowThread;
int * Window::_col = nullptr;
int * Window::_row = nullptr;
Point * Window::_centre = nullptr;

Window::Window()
{
    db<System>(TRC) << ">> Thread Window is initializing...\n";
    _windowThread = new Thread(Window::drawWindow);
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
    std::cout << "DRAWING WINDOW:" 
              << " row = "   << *Window::_row 
              << " | col = " << *Window::_col << std::endl;
    //drawBackground();
    //drawShip(spaceShip, 0);
}

/*
void Window::drawShip(std::shared_ptr<Sprite> sprite, int flags) {   
   //sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
}

void Window::drawBackground() {
   //bg->draw_parallax_background(bgMid.x, 0);
}
*/


__END_API