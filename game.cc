#include "header-files/game.h"

__BEGIN_API

Thread * Game::_shipThread;
Thread * Game::_windowThread;
Thread * Game::_kbThread;

Ship * Game::_ship;
Window * Game::_window;
Input * Game::_kb;

int Game::_w = 800;
int Game::_h = 600;
int Game::_fps = 60;
bool Game::_isRunning = true;

void Game::gameRun() {
    db<System>(TRC) << ">> Game is starting...\n";

    _kbThread = new Thread(Game::kbRun);
    _windowThread = new Thread(Game::windowRun, _w, _h, _fps, &_isRunning);
    _shipThread = new Thread(Game::shipRun);
    
    _kbThread->join();
    _windowThread->join();
    _shipThread->join();

    delete _kbThread;
    delete _windowThread;
    delete _shipThread;

    db<System>(TRC) << ">> Game is ending...\n";
}

void Game::kbRun() {

}

void Game::shipRun() {
    _ship = new Ship(_kb);
    _window->attachShip(_ship); _ship->attachWindow(_window);
    _ship->runShip();
    //DELETE SHIP (????)
}

void Game::windowRun(int w, int h, int fps,  bool * isRunning) {
    _window = new Window(w, h, fps, isRunning);
    _window->runWindow();
    delete _window;
}



void Game::gameLoop() {
    ALLEGRO_EVENT event;
    bool redraw = true;
    
    // input
    // irá retornar uma tecla de ação. TODO: necessário transformar em Thread e fazer a ação
    al_get_keyboard_state(&_kb);

    // get event
    al_wait_for_event(_eventQueue, &event);
    // _display closes
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        _finish = true;
        return;
    }
    
    // timer
    if (event.type == ALLEGRO_EVENT_TIMER) {
        _crtTime = al_current_time();
        update(_crtTime - _prevTime);
        _prevTime = _crtTime;
        redraw = true;
    }
    
    // render
    if (redraw && al_is_event_queue_empty(_eventQueue)) {
        redraw = false;      
        draw();
        al_flip_display();
    }

}

// update the game mode
void Game::update(double dt) {
    //Spaceship
    centre = centre + speed * dt;
    selectShipAnimation(); // must happen before we reset our speed

    speed = Vector(0, 0); // reset our speed
    checkBoundary();

    // background
    bgMid = bgMid + bgSpeed * dt;   
    if (bgMid.x >= 800) {
        bgMid.x = 0;
    }
}

// draws for the game mode
void Game::draw() {   
    drawBackground();
    drawShip(spaceShip, 0);
    drawLives();
}

void Game::drawShip(std::shared_ptr<Sprite> sprite, int flags) {   
   sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
}
void Game::drawBackground() {
   bg->draw_parallax_background(bgMid.x, 0);
}

void Game::drawLives() {
   Point centre(_displayWidth-70, _displayWidth-50);
   al_draw_rectangle(_displayWidth-50, 40, _displayWidth-50, 70, al_map_rgb(0, 255, 0), 5);
   al_draw_rectangle(_displayWidth-90, 40, _displayWidth-90, 70, al_map_rgb(0, 255, 0), 5); 
   al_draw_rectangle(_displayWidth-130, 40, _displayWidth-130, 70, al_map_rgb(0, 255, 0), 5);
}

void Game::selectShipAnimation() {
   if (speed.x > 0) {
      col = 1;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   } else {
      col = 0;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   }
}

void Game::checkBoundary() {   
   // check x bound and adjust if out
   if (centre.x > 800 - 16)
      centre.x = 800 - 16;
   else if (centre.x < 16)
      centre.x = 16;   
   // check y bound and adjust if out
   if (centre.y > 600 - 16)
      centre.y = 600 - 16;
   else if (centre.y < 16)
      centre.y = 16;
}

void Game::loadSprites()
{
    // Create Ship
    centre = Point(215, 245);
    color= al_map_rgb(0, 200, 0);

    // represents the middle of the image width-wise, and top height-wise
    bgMid = Point(0, 0);
    fgMid = Point(800, 0);
    fg2Mid= Point(300, 300);
    bgSpeed = Vector(50, 0);
    fgSpeed = Vector(-90, 0);

    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/')); 

    // sprites
    spaceShip = std::make_shared<Sprite> ("Sprite2.png"); //espaçonave do usuário
    bg = std::make_shared<Sprite> ("BGstars.png"); //fundo da tela - background
    
    // delete path 
    al_destroy_path(path);
}

__END_API
