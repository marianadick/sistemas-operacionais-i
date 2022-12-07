#include "input.h"

__BEGIN_API

Thread * Input::_inputThread;

Input::Input(act::action * actionPlayer)
{
    db<System>(TRC) << ">> Thread Input is initializing...\n";
    Input * _input = this;
    //_actionPlayer = actionPlayer;
    //std::cout << actionPlayer << std::endl;
    _inputThread = new Thread(Input::inputHandler, _input);
}

Input::~Input()
{
    delete _inputThread;
}

void Input::join()
{
    if (_inputThread)
        _inputThread->join();
    else
        db<CPU>(ERR) << ">> Unnable to join Thread Input.\n";
}

void Input::inputHandler(Input * _input) {
    /*
    if (al_key_down(&kb, ALLEGRO_KEY_UP)) {
        speed.y -= 250;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_RIGHT)) {
        speed.x += 250;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_DOWN)) {
        speed.y += 250;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_LEFT)) {
        speed.x -= 250;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_1)) {
        std::cout << "missel\n";
        *input->_actionPlayer = act::action::FIRE_PRIMARY;
        return 
    }
    if (al_key_down(&kb, ALLEGRO_KEY_SPACE)) {
        std::cout << "tiro normal\n";
        *input->_actionPlayer = act::action::FIRE_SECONDARY;
        return;
    }
    if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE)) {
        std::cout << "sair\n";
        _actionPlayer = act::action::QUIT_GAME;
        return;
    }
    _actionPlayer = act::action::NO_ACTION;
    return;
    */
   std::cout << "INPUUUUUUUUUT" << std::endl;
}

__END_API