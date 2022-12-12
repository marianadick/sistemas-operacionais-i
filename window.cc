#include "header-files/window.h"

__BEGIN_API

Window::Window() {
  db<System>(TRC) << ">> Window is initializing...\n";
  al_init();
  // create the display
  if ((_display = al_create_display(_widthDisplay, _heightDisplay)) == nullptr) {
	std::cout << "Cannot initialize the display\n";
	exit(1);
  }

  // initialize addons
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();

  // initialize our timers
  if ((_timer = al_create_timer(1.0 / _fps)) == nullptr) {
	std::cout << "error, could not create timer\n";
	exit(1);
  }
  if ((_eventQueue = al_create_event_queue()) == nullptr) {
	std::cout << "error, could not create Window event queue\n";
	exit(1);
  }

  // register our allegro _eventQueue
  al_register_event_source(_eventQueue, al_get_display_event_source(_display));
  al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
  al_start_timer(_timer);

  loadSprites();
}

Window::Window(int w, int h, int fps) :
	_widthDisplay(w),
	_heightDisplay(h),
	_fps(fps) {
  db<System>(TRC) << ">> Window is initializing...\n";
  al_init();
  // create the display
  if ((_display = al_create_display(_widthDisplay, _heightDisplay)) == nullptr) {
	std::cout << "Cannot initialize the display\n";
	exit(1);
  }

  // initialize addons
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();

  // initialize timers
  if ((_timer = al_create_timer(1.0 / _fps)) == nullptr) {
	std::cout << "error, could not create timer\n";
	exit(1);
  }
  if ((_eventQueue = al_create_event_queue()) == nullptr) {
	std::cout << "error, could not create Window event queue\n";
	exit(1);
  }

  // register our allegro _eventQueue
  al_register_event_source(_eventQueue, al_get_display_event_source(_display));
  al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
  al_start_timer(_timer);

  loadSprites();
}

Window::~Window() {
  if (_timer != nullptr) al_destroy_timer(_timer);
  if (_eventQueue != nullptr) al_destroy_event_queue(_eventQueue);
  if (_display != nullptr) al_destroy_display(_display);

  _bgSprite.reset();
  db<System>(TRC) << ">> Window destroyed...\n";
}

void Window::runWindow() {
  while (Configs::_isGameRunning) {
	if (_ship == nullptr)
	  Thread::yield();
	checkEvent();
	Thread::yield();
  }
}

void Window::checkEvent() {
  ALLEGRO_EVENT event;
  al_wait_for_event(_eventQueue, &event);
  // _display closes
  if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	Configs::_isGameRunning = false;
	return;
  }

  // Should check if ESC was pressed, exiting the game if so (NOT WORKING)
  if (_kb != nullptr) {
	if (_kb->checkPressedKey(act::action::QUIT_GAME)) {
	  Configs::_isGameRunning = false;
	  return;
	}
  }

  // timer
  if (event.type == ALLEGRO_EVENT_TIMER) {
	drawWindow();
  }
}

void Window::drawWindow() {
  float crtTime;

  // render
  if (al_is_event_queue_empty(_eventQueue)) {
	crtTime = al_current_time();

	// get time difference
	double dt = crtTime - _prevTime;

	// update background
	updateBg(dt);

	// draw and update ship
	if (_ship != nullptr) {
	  _ship->update(dt);
	  _ship->draw();
	}

	// draw and update variable elements
	drawEnemies(dt);
	drawProjectiles(dt);
  drawShipLives();

	// update previous time
	_prevTime = crtTime;

	al_flip_display();
  }
}

void Window::updateBg(double dt) {
  // update
  _bgMid = _bgMid + _bgSpeed * dt;
  if (_bgMid.x >= 800)
	_bgMid.x = 0;

  // draw
  _bgSprite->draw_parallax_background(_bgMid.x, 0);
}

void Window::loadSprites() {
  // represents the middle of the image width-wise, and top height-wise
  _bgMid = Point(0, 0);
  _fgMid = Point(800, 0);
  _fg2Mid = Point(300, 300);
  _bgSpeed = Vector(50, 0);
  _fgSpeed = Vector(-90, 0);

  // Go to resources directory
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));

  // sprites
  _bgSprite = std::make_shared<Sprite>("BGstars.png");

  // delete path
  al_destroy_path(path);
}

void Window::drawEnemies(double dt) {
  for (auto listItem = enemies.begin(); listItem != enemies.end();) {
    Enemy *enemy = *listItem;
    listItem++;

    enemy->update(dt);
    enemy->draw();
  }
}

void Window::drawProjectiles(double dt) {
  for (auto listItem = projectiles.begin(); listItem != projectiles.end();) {
    Projectile *projectiles = *listItem;
    listItem++;

    projectiles->update(dt);
    projectiles->draw();
  }
}

void Window::drawShipLives() {
  int shipLives = _ship->getShipLives();
   Point centre(_widthDisplay-70, _widthDisplay-50);
   if (shipLives > 0) {
	    al_draw_rectangle(_widthDisplay - 70, 50, _widthDisplay - 50, 70,
			al_map_rgb(0, 255, 0), 5);
   }
   if (shipLives > 1) {
      al_draw_rectangle(_widthDisplay - 110, 50, _widthDisplay - 90, 70,
			al_map_rgb(0, 255, 0), 5);
   }
   if (shipLives > 2) {
      al_draw_rectangle(_widthDisplay - 150, 50, _widthDisplay - 130, 70,
			al_map_rgb(0, 255, 0) , 5);
   }
}

void Window::addEnemy(Enemy *enemy)
{
  enemies.push_front(enemy);
}

void Window::removeEnemy(Enemy *enemy)
{
  enemies.remove(enemy);
}

void Window::addProjectile(Projectile *projectile)
{
  projectiles.push_front(projectile);
}

void Window::removeProjectile(Projectile *projectile)
{
  projectiles.remove(projectile);
}

void Window::attachShip(Ship *ship)
{
  _ship = ship;
}

void Window::attachKb(Input *kb)
{
  _kb = kb;
}

__END_API