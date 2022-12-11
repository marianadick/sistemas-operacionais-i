#ifndef window_h
#define window_h

#include <allegro5/allegro.h>
#include <memory>
#include <list> 
#include "traits.h"
#include "thread.h"

#include "ship.h"
#include "input.h"

#include "Vector.h"
#include "Sprite.h"

#include "Drawable.h"

__BEGIN_API
//class Ship;

class Window
{
    public:
        Window(int w, int h, int fps);
        ~Window();

        void runWindow();

        void addDrawableItem(Drawable *item) { this->drawableItens.push_front(item); }
        void removeDrawableItem(Drawable *item) { this->drawableItens.remove(item); }

        void attachShip(Ship * ship); // Link ship to window
        void attachKb(Input * kb); // Link keyboard to window (QUIT game)

    protected:
    private:
        std::list<Drawable *> drawableItens;

        void checkEvent();
        void drawWindow();
        void updateBg(double dt);
        void loadSprites();

        /* Display parameters */
        int _widthDisplay;
        int _heightDisplay;
        int _fps;

        // Background
        Point _bgMid; /**<point used by the background to draw from */
        Point _fgMid;
        Point _fg2Mid;
        Vector _bgSpeed; /**<background movement speed */
        Vector _fgSpeed;
        std::shared_ptr<Sprite> _bgSprite; /**<shared pointer to background animation */
        std::shared_ptr<Sprite> _fgSprite;

        /* Allegro related */
        ALLEGRO_DISPLAY * _display;
        ALLEGRO_TIMER * _timer;
        ALLEGRO_EVENT_QUEUE * _eventQueue;

        /* Timer */
        float _prevTime;

        /* Reference to game state and obj*/
        Ship * _ship;
        Input * _kb;
};

__END_API

#endif