#include "board.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <util.h>

Board::Board(const int size){
    board_size = size;
    board.resize(board_size);
    randomizeBoard();
}

Board::Board(Board* b){
    board_size = b->board_size;
    current_pos = b->current_pos;
    board.resize(board_size);
    board = b->board;
}

void Board::resetBoard(){
    for(int i = 0; i < board_size; i++){
        board[i] = 0;
    }
}

void Board::randomizeBoard(){
    int k;
    int verify[board_size];
    for(int i = 0; i < board_size; i++){
        verify[i]=0;
    }

    for(int i = 0; i < board_size; i++){
        do{
            k = rand() % board_size;
        }while(verify[k] == 1);
        board[i] = k;
        verify[k] = 1;
        if(k == 0)
            current_pos = i;
    }

}

void Board::printBoard(){
    int k = sqrt(board_size);

    for(int i = 0; i < board_size; i++){
        std::cout << board[i] << "\t";
        if((i+1) % k == 0)
            std::cout << std::endl;
    }
}

std::vector<int> Board::availableMoves(){

    std::vector<int> moves;
    int k = sqrt(board_size);

    // get 0 position
    std::pair<int, int> matrix_pos = util::getArrayToMatrixIndex(current_pos, k);

    // check MOVE_UP
    if(matrix_pos.second - 1 >= 0)
        moves.push_back(MOVE_UP);

     // check MOVE_DOWN
    if(matrix_pos.second + 1 <= k-1)
        moves.push_back(MOVE_DOWN);

    // check MOVE_LEFT
    if(matrix_pos.first - 1 >= 0)
        moves.push_back(MOVE_LEFT);

    // check MOVE_RIGHT
    if(matrix_pos.first + 1 <= k-1)
        moves.push_back(MOVE_RIGHT);

    return moves;
}

bool Board::doMove(int move){
    return true;
}

Board::~Board(){
    board.clear();
}
