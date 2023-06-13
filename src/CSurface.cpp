#include "CSurface.h"
#include <SDL/SDL_video.h>
#include <cstddef>

CSurface::CSurface(){

}

// loads surface with bmp image in memory
SDL_Surface* CSurface::OnLoad(char *file){
    SDL_Surface* Surf_temp = NULL;
    SDL_Surface* Surf_return = NULL;

    // loads bmp on Surf_temp 
    if ((Surf_temp = SDL_LoadBMP(file)) == NULL) {
        return NULL;
    }

    // manages surface formatting
    Surf_return = SDL_DisplayFormat(Surf_temp);
    
    SDL_FreeSurface(Surf_temp);

    return Surf_return;
}


// draws stuff a sirface on display surface 
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_src, int x, int y){
    // checks if surfaces are not null
    if(Surf_Dest == NULL || Surf_src == NULL) {
        return false;
    }

    // DestR rectangle will give
    SDL_Rect DestR;

    DestR.x = x;
    DestR.y = y;

    SDL_BlitSurface(Surf_src, NULL, Surf_Dest, &DestR);

    return true;
}

// can crop original image (x2 and y2)and draw it on the surface

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_src, int x, int y, int x2, int y2, int w, int h){

    // DestR decides where to draw image
    // SrcR decides which part of image to draw
    if( Surf_Dest == NULL || Surf_src == NULL) return false;

    SDL_Rect DestR;

    DestR.x = x;
    DestR.y = y;

    SDL_Rect SrcR;
    SrcR.x = x2;
    SrcR.y = y2;
    SrcR.h = h;
    SrcR.w = w;

    
    SDL_BlitSurface(Surf_src, &SrcR, Surf_Dest, &DestR);

    return true;

}

bool CSurface::Transparent(SDL_Surface *Surf_Dest, int R, int G, int B){
     if(Surf_Dest == NULL) {
        return false;
    }
 
    SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));

    return true;
}
