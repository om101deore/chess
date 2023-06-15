#include <iostream>
#include "CBoard.h"
#include "capp.h"
#include "CEvent.h"
#include "CSurface.h"
#include "Define.h"
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_video.h>
#include <cstddef>

Capp::Capp(){
    Surf_display = NULL;
    running = true;

}

Capp::~Capp(){

}


bool Capp::onInit(){
    // initialization of SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }

    // checking if Surf_display is loaded properly
    if((Surf_display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL ){
        return false;
    }
    
    // loading board in memory
    if(board.OnLoad((char*)"../boards/normal.brd") == false) return false;
   

    return true;
}

// execution of gameret
int Capp::onExecute(){

    if(onInit() == false) return -1;
    
    SDL_Event Event;
    while (running) {
        // takes all events and adds them in queue
        // SDL_PollEvent pops event one by one into event var
        while (SDL_PollEvent(&Event)) {
            onEvent(&Event);
        
        }

        onLoop();
        onRender();
    }

    onCleanup();
    return 0;
}

void Capp::onEvent(SDL_Event *Event){
    CEvent::OnEvent(Event);
}

// Does calculations and all
void Capp::onLoop(){

}

//Does all displying jobs
void Capp::onRender(){

    board.OnRender(Surf_display);

    // clears whole screen
//    SDL_FillRect(Surf_display, NULL, 0x000000);


    board.OnRender(Surf_display);

    // something for double buffering
    SDL_Flip(Surf_display);

}

void Capp::onCleanup(){

    board.OnCleanup();

    SDL_Quit();

}

// OnExit is inherited from CEvent and we can add what we want to do in that event
void Capp::OnExit(){
    running = false;
}

void Capp::OnLButtonDown(int mX, int mY){
    board.SwapPieces1( mX, mY);

}

int main (int argc, char *argv[])
{
    Capp app;

    return app.onExecute();
}
