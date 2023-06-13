#include "Define.h"
#include "CBoard.h"
#include "CPiece.h"
#include "CSurface.h"
#include <SDL/SDL_video.h>
#include <bits/types/FILE.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <utility>

CBoard::CBoard(){
    Surf_board = NULL;
    Surf_piece = NULL;

    firstClickDone = false;
    startX = startY = endX = endY = 0;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            pieceBoard[i][j].color = 0;
            pieceBoard[i][j].PieceType = PIECE_NONE;
        }
    }

}

bool CBoard::OnLoad(char *File){
    if ((Surf_board = CSurface::OnLoad((char*)"../assets/board-real.bmp")) == NULL) {
        return false; 
    }

    if ((Surf_piece = CSurface::OnLoad((char*)"../assets/pieces1.bmp")) == NULL) {
        return false; 
    }
    CSurface::Transparent(Surf_piece, 255, 0, 255);


    FILE* FileHandle = fopen(File, "r");
    if(!FileHandle) return false;

    //  for checking if file read correctly
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0;  j < 8; j++) {
            Piece tempPiece;

            fscanf(FileHandle, "%d:%d ", &tempPiece.color, &tempPiece.PieceType);

            tempPiece.posX = j;
            tempPiece.posY = i;
            pieceBoard[i][j] = tempPiece;

        }
        fscanf(FileHandle, "\n");
    } 

    // load move texture
    move.OnLoad();

    return true;
}

void CBoard::OnRender(SDL_Surface *Surf_display){
    CSurface::OnDraw(Surf_display, Surf_board, 0, 0);

    int src_X = 0;
    int src_Y = 0;

    int dest_X = 0;
    int dest_Y = 0;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {

            Piece curr = pieceBoard[j][i];



            if(curr.color == 0) continue;

            src_X = (curr.PieceType - 1)*BOX_WIDTH;
            src_Y = (curr.color - 1)*BOX_HEIGHT;

            dest_X = curr.posX*BOX_WIDTH + 25;
            dest_Y = curr.posY*BOX_WIDTH + 25;


            CSurface::OnDraw(Surf_display,Surf_piece, dest_X, dest_Y, src_X, src_Y,  BOX_WIDTH, BOX_HEIGHT);
                 
        }
    }

    move.OnRender(Surf_display);
}

void CBoard::OnCleanup(){
    SDL_FreeSurface(Surf_board);
    SDL_FreeSurface(Surf_piece);
}

void CBoard::SwapPieces(int mX, int mY){
    if (!firstClickDone) {
        startX = mX;
        startY = mY;

        startI = (startX - 25) / BOX_WIDTH;
        startJ = (startY - 25) / BOX_WIDTH;


        firstClickDone = true;
    }
    else if (firstClickDone) {
        endX = mX;
        endY = mY;

        firstClickDone = false;
    }

    if (firstClickDone == false) {
        // do swap
        endI = ( endX - 25) / BOX_WIDTH;
        endJ = ( endY - 25) / BOX_WIDTH;


        if(move.validMoveArr[endJ][endI] == true){
            std::cout << "Beofre swap" << std::endl;
            Piece startTemp;

            startTemp = pieceBoard[startJ][startI];
            pieceBoard[startJ][startI] = pieceBoard[endJ][endI];
            pieceBoard[endJ][endI] = startTemp;

            std::cout << "After swap" << std::endl;

            pieceBoard[startJ][startI].posX = startI;
            pieceBoard[startJ][startI].posY = startJ;

            pieceBoard[endJ][endI].posX = endI;
            pieceBoard[endJ][endI].posY = endJ;


            if(pieceBoard[startJ][startI].PieceType != PIECE_NONE){
                
                pieceBoard[startJ][startI].PieceType = PIECE_NONE;
                pieceBoard[startJ][startI].color = 0;
                
            }

        }

        move.ClearBoard();
    }
    else {
        std::cout<< "Before CheckMoves" << std::endl;
        move.CheckMoves(pieceBoard[startJ][startI], pieceBoard);
    }

}
