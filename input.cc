#include "header-files/input.h"

__BEGIN_API

Input::Input()
{
    db<System>(TRC) << ">> Input Handler is initializing...\n";
    // install keyboard
    if (!al_install_keyboard()) {
        std::cerr << "Could not install keyboard\n";
        exit(1);
    }

    if ((_eventQueue = al_create_event_queue()) == NULL) {
        std::cout << "error, could not create Input event queue\n";
        exit(1);
    }
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
}

Input::~Input()
{
    db<System>(TRC) << ">> Input Handler destroyed...\n";
}

void Input::runInput()
{
    while (Configs::_isGameRunning) {
        al_get_keyboard_state(&_kb); // getting kb state
        Thread::yield();
    }
}

bool Input::checkPressedKey(act::action key)
{
    // Quit game key
    if (key == act::action::QUIT_GAME) {
        return al_key_down(&_kb, ALLEGRO_KEY_ESCAPE);
    }

    // Fire keys
    else if (key == act::action::FIRE_SECONDARY)
        return al_key_down(&_kb, ALLEGRO_KEY_1);
    else if (key == act::action::FIRE_PRIMARY)
        return al_key_down(&_kb, ALLEGRO_KEY_SPACE);

    // Movement keys
    else if (key == act::action::MOVE_UP)
        return al_key_down(&_kb, ALLEGRO_KEY_UP);
    else if (key == act::action::MOVE_DOWN)
        return al_key_down(&_kb, ALLEGRO_KEY_DOWN);
    else if (key == act::action::MOVE_LEFT)
        return al_key_down(&_kb, ALLEGRO_KEY_LEFT);
    else if (key == act::action::MOVE_RIGHT)
        return al_key_down(&_kb, ALLEGRO_KEY_RIGHT);

    return false;
}

__END_API