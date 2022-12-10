#include "header-files/window.h"
#include "header-files/configs.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

__BEGIN_API

Window::Window(int w, int h, int fps) :
    _widthDisplay(w),
    _heightDisplay(h),
    _fps(fps)
{
    db<System>(TRC) << ">> Window is initializing...\n";
    al_init();
    // create the display
    if ((_display = al_create_display(_widthDisplay, _heightDisplay)) == NULL) {
        std::cout << "Cannot initialize the display\n";
        exit(1); 
    }

    // initialize addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    // initialize our timers
    if ((_timer = al_create_timer(1.0 / _fps*1.5)) == NULL) {
        std::cout << "error, could not create timer\n";
        exit(1);
    }
    if ((_eventQueue = al_create_event_queue()) == NULL) {
        std::cout << "error, could not create Window event queue\n";
        exit(1);
    }

    // register our allegro _eventQueue
    al_register_event_source(_eventQueue, al_get_display_event_source(_display)); 
    al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
    al_start_timer(_timer);

    // install keyboard
    if (!al_install_keyboard()) {
        std::cerr << "Could not install keyboard\n";
        exit(1);
    }

    // register keyboard
    al_register_event_source(_eventQueue, al_get_keyboard_event_source());
    loadSprites();
}

Window::~Window()
{
    if (_timer != NULL) al_destroy_timer(_timer);
    if (_eventQueue != NULL) al_destroy_event_queue(_eventQueue);
    if (_display != NULL) al_destroy_display(_display);

    _bgSprite.reset();
    db<System>(TRC) << ">> Window destroyed...\n";
}

void Window::runWindow()
{
    while(Configs::_isGameRunning) {
        checkEvent();
        Thread::yield();
    }
}

void Window::drawWindow()
{
    float crtTime;
    // render
    if (al_is_event_queue_empty(_eventQueue)) {
        crtTime = al_current_time();

        updateBg(crtTime - _prevTime);

        if (_ship != nullptr)
        {
            _ship->update(crtTime - _prevTime);
            _ship->draw();
        }
        _prevTime = crtTime;
        al_flip_display();
    }
}

void Window::updateBg(double dt)
{
    // update
    _bgMid = _bgMid + _bgSpeed * dt;
    if (_bgMid.x >= 800)
        _bgMid.x = 0;

    // draw
    _bgSprite->draw_parallax_background(_bgMid.x, 0);
}

void Window::checkEvent() 
{
    ALLEGRO_EVENT event;
    al_wait_for_event(_eventQueue, &event);
    // _display closes
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        Configs::_isGameRunning = false;
        return;
    }
    
    // timer
    if (event.type == ALLEGRO_EVENT_TIMER) {
        drawWindow();
    }
}

void Window::loadSprites() 
{
    // represents the middle of the image width-wise, and top height-wise
    _bgMid = Point(0, 0);
    _fgMid = Point(800, 0);
    _fg2Mid= Point(300, 300);
    _bgSpeed = Vector(50, 0);
    _fgSpeed = Vector(-90, 0);

    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/')); 

    // sprites
    _bgSprite = std::make_shared<Sprite> ("BGstars.png");
    
    // delete path 
    al_destroy_path(path);
}

void Window::attachShip(Ship * ship) 
{
    _ship = ship;
}

void Window::attachKb(Input * kb)
{
    _kb = kb;
}

__END_API