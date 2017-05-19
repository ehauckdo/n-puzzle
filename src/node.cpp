#include "node.h"
#include <cstddef>
#include <iostream>

Node::Node(Board* b){
    board = new Board(b);

    for(int i = 0; i < b->availableMoves(); i++){
        children.push_back(NULL);
    }
}

bool Node::isfullyExpanded(){
    for(int i = 0; i < board->availableMoves(); i++){
        if(children[i] == NULL)
            return false;
    }
    return true;
}

bool Node::expand(int move){
    if(children[move] != NULL)
        return false;

    Board expanded_b(board);
    expanded_b.doMove(move);
    children[move] = new Node(&expanded_b);
    return true;
}


Node::~Node(){
    delete board;
}
