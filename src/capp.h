#pragma once

#include "CBoard.h"
#include "CEvent.h"
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

class Capp : public CEvent{

    public:
        Capp();
        ~Capp();

        int onExecute();

        bool onInit();
        void onEvent(SDL_Event* Event);
        void OnExit();
        void OnLButtonDown(int mX, int mY);
        void onLoop();
        void onRender();
        void onCleanup();

    private:
        bool running;
        SDL_Surface* Surf_display;

        CBoard board;
};


