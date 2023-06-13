#pragma once
#include <SDL/SDL.h>


class CSurface{
    public:
    CSurface();

    static SDL_Surface* OnLoad(char* file);

    // x and y are offset in resp direction
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_src, int x, int y);
    
    // x1, y1 --> position where image displays
    // x2, y2 --> position from where image of src starts 
    // w, h width and height of image to be rendered
    //                  dest        src     x1 y1 x2 y2 w h
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_src, int x, int y, int x2, int y2, int w, int h);
    
    // Transparents color with values RGB
    static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
};
