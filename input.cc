#include "input.h"

__BEGIN_API

Thread * Input::_inputThread;

Input::Input(act::action * actionPlayer, bool * finish, ALLEGRO_KEYBOARD_STATE *kb, Vector *speed)
{
    db<System>(TRC) << ">> Thread Input is initializing...\n";
    _pointer = this;
    _actionPlayer = actionPlayer;
    _finish = finish;
    _kb = kb; 
    _speed = speed; 
    //_inputThread = new Thread(Input::inputHandler, _pointer);
}

Input::~Input()
{
    delete _inputThread;
}

void Input::join()
{
    _inputThread = new Thread(Input::inputHandler, _pointer);
    if (_inputThread) {
        _inputThread->join();
    }
    else
        db<CPU>(ERR) << ">> Unnable to join Thread Input.\n";
}

void Input::inputHandler(Input * _input) {
    *_input->_actionPlayer = act::action::NO_ACTION;
    if (al_key_down(_input->_kb, ALLEGRO_KEY_UP)) {
        _input->_speed->y -= 250;
    }
    if (al_key_down(_input->_kb, ALLEGRO_KEY_RIGHT)) {
        _input->_speed->x += 250;
    }
    if (al_key_down(_input->_kb, ALLEGRO_KEY_DOWN)) {
        _input->_speed->y += 250;
    }
    if (al_key_down(_input->_kb, ALLEGRO_KEY_LEFT)) {
        _input->_speed->x -= 250;
    }
    if (al_key_down(_input->_kb, ALLEGRO_KEY_1)) {
        std::cout << "missel\n";
        *_input->_actionPlayer = act::action::FIRE_PRIMARY;
    }
    if (al_key_down(_input->_kb, ALLEGRO_KEY_SPACE)) {
        std::cout << "tiro normal\n";
        *_input->_actionPlayer = act::action::FIRE_SECONDARY;
    }
    if (al_key_down(_input->_kb, ALLEGRO_KEY_ESCAPE)) {
        std::cout << "sair\n";
        *_input->_actionPlayer = act::action::QUIT_GAME;
    }
    _input->_inputThread->thread_exit(3);
    //delete _input->_inputThread;
}

__END_API