#include "board.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <util.h>
#include <stdexcept>

Board::Board(const int size){
    board_size = size;
    board.resize(board_size);
    randomizeBoard();
}

Board::Board(Board* b){
    board_size = b->board_size;
    current_pos = b->current_pos;
    //board.resize(board_size);
    for(std::vector<int>::iterator it = b->board.begin(); it != b->board.end(); it++){
        std::cout << *it << std::endl;
        board.push_back(*it);
    }
    std::cout << std::endl;
    //board = b->board;
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
//    std::cout  << "MATRIX POS:" << matrix_pos.first << ", " << matrix_pos.second << std::endl;

    // check MOVE_UP
    if(matrix_pos.first - 1 >= 0)
        moves.push_back(MOVE_UP);

     // check MOVE_DOWN
    if(matrix_pos.first + 1 <= k-1)
        moves.push_back(MOVE_DOWN);

    // check MOVE_LEFT
    if(matrix_pos.second - 1 >= 0)
        moves.push_back(MOVE_LEFT);

    // check MOVE_RIGHT
    if(matrix_pos.second + 1 <= k-1)
        moves.push_back(MOVE_RIGHT);

    return moves;
}

bool Board::doMove(int move){

    std::pair<int, int> pos_0 = util::getArrayToMatrixIndex(current_pos, sqrt(board_size));
    std::pair<int, int> new_pos;

    std::vector<int> availableMoves = this->availableMoves();
//    std::cout <<"Available moves:" << std::endl;
//    for(std::vector<int>::iterator it = availableMoves.begin(); it != availableMoves.end(); it++)
//        std::cout << *it << ", ";
//    std::cout << std::endl;

    if(util::contains(availableMoves, move) == false)
        return false;

    switch(move){
        case MOVE_UP:
            new_pos.first = pos_0.first-1;
            new_pos.second = pos_0.second;
            break;
        case MOVE_DOWN:
            new_pos.first = pos_0.first+1;
            new_pos.second = pos_0.second;
            break;
        case MOVE_LEFT:
            new_pos.first = pos_0.first;
            new_pos.second = pos_0.second-1;
            break;
        case MOVE_RIGHT:
            new_pos.first = pos_0.first;
            new_pos.second = pos_0.second+1;
            break;
    }

    int index_to_change = util::getMatrixToArrayIndex(new_pos, sqrt(board_size));

    this->board[current_pos] = board[index_to_change];
    this->board[index_to_change] = 0;

    current_pos = index_to_change;
//    std::cout << "index to change:" << index_to_change << std::endl;
    return true;
}

Board::~Board(){
    board.clear();
}
