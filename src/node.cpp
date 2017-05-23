#include "node.h"
#include <cstddef>
#include <iostream>

Node::Node(Board* b, int executedMove){
    board = new Board(b);
    lastMove = executedMove;
    int availableMoves = board->availableMoves().size();

    int n_moves = (lastMove == -1) ? availableMoves : availableMoves-1;

    for(int i = 0; i < n_moves; i++){
        children.push_back(NULL);
    }
}

bool Node::isfullyExpanded(){
    int availableMoves = board->availableMoves().size();
    int n_moves = lastMove == -1 ? availableMoves : availableMoves-1;

    for(int i = 0; i < n_moves; i++){
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
    children[move] = new Node(&expanded_b, move);
    return true;
}


Node::~Node(){
    delete board;
}
