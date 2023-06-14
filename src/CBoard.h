#pragma once

#include "CPiece.h"
#include "CSurface.h"
#include "CMoves.h"
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

class CBoard{
    public:
    CBoard();
    bool OnLoad(char* File);
    void OnRender(SDL_Surface* Surf_display);
    void OnCleanup();
    void SwapPieces(int mX, int mY);
    void SwapPieces1(int mX, int mY);
    
    private:
    SDL_Surface* Surf_board;
    SDL_Surface* Surf_piece;
    CMove move;    
    Piece pieceBoard[8][8];
    bool firstClickDone;
    bool whiteTurn;
   
    int startX, startY;
    int endX, endY;
    int startI;
    int startJ;   
    int endI;    
    int endJ;



       
};
