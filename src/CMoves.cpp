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
#include <cmath>

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
    
    if(selPiece.PieceType == PIECE_NONE) {
        return;
    }

    selI = selPiece.posY;
    selJ = selPiece.posX;


    switch (selPiece.PieceType) {
        // PAWN---------------------------------------------
        case PIECE_PAWN:
            // white
            if(selPiece.color == 1){
                i = selI -1;
                j = selJ ;

                if (pieceArr[i][j].PieceType == 0) {
                    validMoveArr[i][j] = true;

                    if(selI == 6)
                        validMoveArr[i - 1][j] = true;
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

            // black
            else if(selPiece.color == 2){
                i = selI +1;
                j = selJ ;

                if (pieceArr[i][j].PieceType == 0) {
                    validMoveArr[i][j] = true;

                    if(selI == 1)
                        validMoveArr[i + 1][j] = true;
                }
                
                i = selI + 1;
                j = selJ + 1;
                if(pieceArr[i][j].PieceType != PIECE_NONE
                    && pieceArr[i][j].color == 1){
                    validMoveArr[i][j] = true;
                }

                i = selI + 1;
                j = selJ - 1;
                if(pieceArr[i][j].PieceType != PIECE_NONE
                    && pieceArr[i][j].color == 1){
                    validMoveArr[i][j] = true;
                }


               
            }

            break;

    
        case PIECE_KING:
            if(selPiece.color == 1){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {
                        

                        selI = selPiece.posY;
                        selJ = selPiece.posX;


                        i = selI + n;
                        j = selJ + m;

                        if(i < 0 || j < 0) continue;
                        if(i > 7 || j > 7) continue;

                        if(pieceArr[i][j].color == 1) continue;

                        validMoveArr[i][j] = true;

                    }

                }
            }
            
            if(selPiece.color == 2){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {
                        

                        selI = selPiece.posY;
                        selJ = selPiece.posX;


                        i = selI + n;
                        j = selJ + m;

                        if(i < 0 || j < 0) continue;
                        if(i > 7 || j > 7) continue;

                        if(pieceArr[i][j].color == 2) continue;

                        validMoveArr[i][j] = true;
                    }

                }
            }
            
            break;

        case PIECE_QUEEN:
            if(selPiece.color == 1){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {

                        i = selI;
                        j = selJ;
                       
                        while (true) {

                            i = i + n;
                            j = j + m;


                            if(i < 0 || j < 0) break;
                            if(i > 7 || j > 7) break;

                            if(pieceArr[i][j].color == 1) break;

                            if(pieceArr[i][j].color == 2){
                                validMoveArr[i][j] = true;
                                break;
                            }

                            validMoveArr[i][j] = true;



                        }
                    }


                }
            }
            if(selPiece.color == 2){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {

                        i = selI;
                        j = selJ;
                       
                        while (true) {

                            i = i + n;
                            j = j + m;


                            if(i < 0 || j < 0) break;
                            if(i > 7 || j > 7) break;

                            if(pieceArr[i][j].color == 2) break;

                            if(pieceArr[i][j].color == 1){
                                validMoveArr[i][j] = true;
                                break;
                            }
                            
                            validMoveArr[i][j] = true;



                        }
                    }


                }
            }

            break;

        case PIECE_ROOK:
            if(selPiece.color == 1){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {

                        if(abs(m) == abs(n)) continue;

                        i = selI;
                        j = selJ;
                       
                        while (true) {

                            i = i + n;
                            j = j + m;


                            if(i < 0 || j < 0) break;
                            if(i > 7 || j > 7) break;

                            if(pieceArr[i][j].color == 1) break;

                            if(pieceArr[i][j].color == 2){
                                validMoveArr[i][j] = true;
                                break;
                            }

                            validMoveArr[i][j] = true;
                        }
                    }


                }
            }

            if(selPiece.color == 2){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {

                        if(abs(m) == abs(n)) continue;

                        i = selI;
                        j = selJ;
                       
                        while (true) {

                            i = i + n;
                            j = j + m;


                            if(i < 0 || j < 0) break;
                            if(i > 7 || j > 7) break;

                            if(pieceArr[i][j].color == 2) break;

                            if(pieceArr[i][j].color == 1){
                                validMoveArr[i][j] = true;
                                break;
                            }

                            validMoveArr[i][j] = true;
                        }
                    }


                }
            }
            break;

        case PIECE_BISHOP:
            if(selPiece.color == 1){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {
                        
                        if((abs(m)+abs(n)) == 1) continue;

                        i = selI;
                        j = selJ;
                       
                        while (true) {

                            i = i + n;
                            j = j + m;


                            if(i < 0 || j < 0) break;
                            if(i > 7 || j > 7) break;

                            if(pieceArr[i][j].color == 1) break;

                            if(pieceArr[i][j].color == 2){
                                validMoveArr[i][j] = true;
                                break;
                            }

                            validMoveArr[i][j] = true;
                        }
                    }
                }
            }
            if(selPiece.color == 2){

                for (int n = -1;  n < 2; n++) {
                    for (int m = -1; m < 2; m++) {
                        
                        if((abs(m)+abs(n)) == 1) continue;

                        i = selI;
                        j = selJ;
                       
                        while (true) {

                            i = i + n;
                            j = j + m;


                            if(i < 0 || j < 0) break;
                            if(i > 7 || j > 7) break;

                            if(pieceArr[i][j].color == 2) break;

                            if(pieceArr[i][j].color == 1){
                                validMoveArr[i][j] = true;
                                break;
                            }

                            validMoveArr[i][j] = true;
                        }
                    }
                }
            }

            break;

        case PIECE_KNIGHT:
            if(selPiece.color == 1){

                for (int n = -2;  n < 3; n++) {
                    for (int m = -2; m < 3; m++) {
                        
                        if((abs(m)+abs(n)) != 3) continue;

                        i = selI;
                        j = selJ;
                       

                        i = i + n;
                        j = j + m;


                       if(i < 0 || j < 0) break;
                       if(i > 7 || j > 7) break;

                       if(pieceArr[i][j].color == 1) break;

                       if(pieceArr[i][j].color == 2){
                           validMoveArr[i][j] = true;
                           break;
                       }

                            validMoveArr[i][j] = true;
                    }
                }
            }
            if(selPiece.color == 2){

                for (int n = -2;  n < 3; n++) {
                    for (int m = -2; m < 3; m++) {
                        
                        if((abs(m)+abs(n)) != 3) continue;

                        i = selI;
                        j = selJ;
                       

                        i = i + n;
                        j = j + m;


                       if(i < 0 || j < 0) break;
                       if(i > 7 || j > 7) break;

                       if(pieceArr[i][j].color == 2) break;

                       if(pieceArr[i][j].color == 1){
                           validMoveArr[i][j] = true;
                           break;
                       }

                            validMoveArr[i][j] = true;
                    }
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
