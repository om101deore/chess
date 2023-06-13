#pragma once

#include "CPiece.h"
#include "CSurface.h"
#include <SDL/SDL.h>
#include <SDL/SDL_video.h>

class CMove{
    public:
    CMove();
    bool OnLoad();
    void OnRender(SDL_Surface* Surf_Display);
    void OnCleanup();
    void CheckMoves(Piece selectedPiece, Piece pieceArr[][8]);
    void ClearBoard();

    bool validMoveArr[8][8];

    private:
    SDL_Surface* Surf_loc;

    // i want this class to render grey squares which will show valid moves and will restrict
    // the pieces ; this class will contain all about moves
};
