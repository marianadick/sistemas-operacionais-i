#ifndef game_h
#define game_h

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <memory>
#include <stdexcept>

#include "Timer.h"
#include "Sprite.h"
#include "Vector.h"

#include "input.h"

__BEGIN_API

class Game
{
public:
    Game(int w, int h, int fps);
    
    ~Game();

    static void run(Game * _game);
    void gameLoop();
    act::action input(ALLEGRO_KEYBOARD_STATE& kb);
    void update(double dt);
    void draw();
    void drawShip(std::shared_ptr<Sprite> sprite, int flags);
    void drawBackground();
    void drawLives();

    inline int getWidth() const {
      return _displayWidth;
    }
    inline int getHeight() const {
      return _displayHeight;
    }
    inline int getFps() const {
      return _fps;
    }

    ALLEGRO_KEYBOARD_STATE _kb;

private:
    void selectShipAnimation();
    void checkBoundary();
    void loadSprites();

    static Thread * _gameThread;
    Input * _inputHandler;

    // (old) Engine attributes
    ALLEGRO_DISPLAY *_display;
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;

    // general game variables
    int _fps;
    int _displayWidth;
    int _displayHeight;
    bool _finish;

    float _crtTime;
    float _prevTime;
    act::action _actionPlayer;

    //Background
    Point bgMid;/**<point used by the background to draw from */
    Point fgMid;
    Point fg2Mid;
    Vector bgSpeed;/**<background movement speed */
    Vector fgSpeed;
    std::shared_ptr<Sprite> bg;/**<shared pointer to background animation */
    std::shared_ptr<Sprite> fg;

    std::shared_ptr<Sprite> spaceShip;
    Point centre;        /**< ship position */
    Vector speed;        /**< movement speed in any direction */
    int row;             /**<row of animation to be played */
    int col;             /**< column of animation to be played */
    
    ALLEGRO_COLOR color; /**< ship color */   
};

__END_API

#endif
