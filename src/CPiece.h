#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_video.h>


enum {
    PIECE_NONE = 0,
    PIECE_KING,
    PIECE_QUEEN,
    PIECE_BISHOP,
    PIECE_KNIGHT,
    PIECE_ROOK,
    PIECE_PAWN
};

class Piece {
    public:
    Piece();

    int PieceType;
    int color;
    int posX;
    int posY;
};


