#include "node.h"
#include <cstddef>
#include <iostream>
#include <util.h>
#include <algorithm>

Node::Node(Node* parent, Board* b, int executedMove){
    board = new Board(b);
    parent = parent;
    lastMove = executedMove;
    availableMoves = board->availableMoves();

    if(lastMove != -1){
        std::vector<int>::iterator position = std::find(availableMoves.begin(), availableMoves.end(), lastMove);
        if (position != availableMoves.end())
            availableMoves.erase(position);
    }

    for(int i = 0; i < 4; i++){
        children.push_back(NULL);
    }
}

bool Node::isfullyExpanded(){
    for(std::vector<int>::iterator it = availableMoves.begin(); it != availableMoves.end(); it++){
        if(children[*it] == NULL){
            return false;
        }
    }

    return true;
}

Node* Node::expand(int move){
    if(!util::contains(availableMoves, move) || children[move] != NULL)
        return NULL;

    Board expanded_b(board);
    expanded_b.doMove(move);
    children[move] = new Node(this, &expanded_b, move);
    return children[move];
}

Node* Node::expand(){
    int next_move = -1;
    for(std::vector<int>::iterator it = availableMoves.begin(); it != availableMoves.end(); it++){
        if(children[*it] == NULL){
            next_move = *it;
            break;
        }
    }

    if(next_move == -1)
        return NULL;

    Board expanded_b(board);
    expanded_b.doMove(next_move);
    children[next_move] = new Node(this, &expanded_b, next_move);
    return children[next_move];
}


Node::~Node(){
    delete board;
    for(int i = 0; i < 4; i++){
        delete children[i];
    }
}
