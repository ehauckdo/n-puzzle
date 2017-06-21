#include "node.h"
#include <cstddef>
#include <iostream>
#include <util.h>
#include <algorithm>

int Node::id_counter = 0;

Node::Node(Node* parent, Board* b, int executedMove){
    board = new Board(b);

    this->parent = parent;
    if(parent != NULL)
        this->depth = parent->depth + 1;
    else
        this->depth = 0;
    lastMove = executedMove;
    availableMoves = board->availableMoves();
    id = id_counter++;


    if(lastMove != -1){
        int oppositeMove = util::getOppositeMove(lastMove);
        availableMoves.erase(std::remove(availableMoves.begin(), availableMoves.end(), oppositeMove), availableMoves.end());
        //std::vector<int>::iterator position = std::find(availableMoves.begin(), availableMoves.end(), lastMove);
        //if (position != availableMoves.end())
        //    availableMoves.erase(position);
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

bool Node::isAncestral(Board* b){
    Node *current = this;
    while(current != NULL){
        if(current->board->board == b->board)
            return true;
        current = current->parent;
    }
    return false;
}

Node* Node::expand(int move){
    if(!util::contains(availableMoves, move) || children[move] != NULL)
        return NULL;

    Board* expanded_b = new Board(board);
    expanded_b->doMove(move);
    children[move] = new Node(this, expanded_b, move);
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
    for(int i = 0; i < 4; i++){
        delete children[i];
        children[i] = NULL;
    }
    delete board;
}
