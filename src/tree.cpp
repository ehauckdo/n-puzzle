#include "tree.h"
#include <cstddef>

Tree::Tree(Board *b){
    root = new Node(NULL, b, -1);
}

Tree::~Tree(){
    delete root;
}


void Tree::backTracking(Board* objective){
    Node current(NULL, root->board, -1);
    Node *root_copy = &current;

    std::vector<std::vector<int> > visited_states;
    visited_states.push_back(current.board->board);

    while(current.board != objective){


    }

}
