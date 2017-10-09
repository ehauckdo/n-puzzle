#include "board.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <util.h>
#include <algorithm>

Board::Board(const int size){
    board_size = size;
    board.resize(board_size);
    resetBoard();
}

Board::Board(Board* b){
    board_size = b->board_size;
    current_pos = b->current_pos;
    board = b->board;
}

void Board::resetBoard(){
    for(int i = 0; i < board_size; i++){
        board[i] = i+1;
    }
    board[board_size-1] = 0;
    current_pos = board_size-1;
}

void Board::randomizeBoard(int k){
    srand(4);
    int last_move = -1;
    int next_move = -1;
    bool is_valid_move = false;
    bool is_opposite_move = false;
    for(int i = 0; i < k; i++){
        std::vector<int> moves = this->availableMoves();
        do{
            next_move = rand() % 4;
            is_valid_move = std::find(moves.begin(), moves.end(), next_move) != moves.end();
            is_opposite_move = (next_move == util::getOppositeMove(last_move));

        }while(!is_valid_move || is_opposite_move);

        doMove(next_move);
        last_move = next_move;
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
    return true;
}

int Board::getH1(Board* target){
    int h1 = 0;
    for(int i = 0; i < board_size; i++){
        if(board[i] != target->board[i])
            h1 = h1 + 1;
    }
    return h1;

}

int Board::getH2(Board* target){
    int h2 = 0;
    for(int i = 0; i < board_size; i++){
        std::pair<int, int> pos_init = util::getArrayToMatrixIndex(i, sqrt(board_size));
        for(int j = 0; j < target->board_size; j++){
            if(board[i] == target->board[j]){
                std::pair<int, int> pos_target = util::getArrayToMatrixIndex(j, sqrt(target->board_size));
                h2 = h2 + abs(pos_target.first - pos_init.first);
                h2 = h2 + abs(pos_target.second - pos_init.second);
            }
        }
    }
    return h2;

}

Board::~Board(){
    board.clear();
}
