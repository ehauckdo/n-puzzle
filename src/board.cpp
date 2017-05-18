#include "board.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>

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

int Board::availableMoves(){
    int k = sqrt(board_size);
    std::cout << current_pos << ", " << k<< std:: endl;

    int relative_pos = (current_pos+1) % k;

    if((current_pos < k || current_pos > k*(k-1))
        && (relative_pos == 0 || relative_pos == 1))
        return 2;

    if((current_pos > k || current_pos < k*(k-1))
        && (relative_pos == 0 || relative_pos == 1))
        return 3;

    if((current_pos > k || current_pos < k*(k-1))
        && (relative_pos != 0 && relative_pos != 1))
        return 4;

    return -1;

}

Board::~Board(){
    board.clear();
}
