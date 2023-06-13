#include "CMoves.h"
#include "CPiece.h"
#include "CSurface.h"
#include "Define.h"
#include <iostream>
#include <SDL/SDL_video.h>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <unistd.h>

CMove::CMove(){
    SDL_Surface* Surf_loc = NULL;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0;  j< 8; j++) {
            validMoveArr[i][j] = false;
            
        }
        
    }
}

bool CMove::OnLoad(){
    if((Surf_loc = CSurface::OnLoad((char*)"../assets/grey.bmp")) == NULL) return false;

    CSurface::Transparent(Surf_loc, 255, 0, 255);
    return true;
}

void CMove::OnRender(SDL_Surface* Surf_Display){
    int dest_X, dest_Y;
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0;  j < 8; j++) {

            if(validMoveArr[j][i]){
                dest_X = i * BOX_WIDTH + 25;
                dest_Y = j * BOX_WIDTH + 25;

                CSurface::OnDraw(Surf_Display, Surf_loc, dest_X, dest_Y, 0,0, BOX_WIDTH, BOX_HEIGHT);
            }
        }
    }
}

void CMove::CheckMoves(Piece selPiece, Piece pieceArr[][8]){
    int selI, selJ;
    int i,j;
    
    std::cout<< "in check moves" << std::endl;
    if(selPiece.PieceType == PIECE_NONE) {
        std::cout<< "null piece" << std::endl;
        return;
    }

    selI = selPiece.posY;
    selJ = selPiece.posX;


    switch (selPiece.PieceType) {
        case PIECE_PAWN:
            std::cout<< "checking for pawn" << std::endl;
            // white
            if(selPiece.color == 1){
                std::cout<< "after checking piece color" << std::endl;
                i = selI -1;
                j = selJ ;

                if (pieceArr[i][j].PieceType == 0) {
                    std::cout<< "if piece none" << std::endl;
                    validMoveArr[i][j] = true;
                }
                
                i = selI - 1;
                j = selJ - 1;
                if(pieceArr[i][j].PieceType != PIECE_NONE
                    && pieceArr[i][j].color == 2){
                    validMoveArr[i][j] = true;
                }

                i = selI - 1;
                j = selJ + 1;
                if(pieceArr[i][j].PieceType != PIECE_NONE
                    && pieceArr[i][j].color == 2){
                    validMoveArr[i][j] = true;
                }


               
            } 
    
    }
}

void CMove::ClearBoard(){
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0;  j< 8; j++) {
            validMoveArr[i][j] = false;
            
        }
        
    }
}
