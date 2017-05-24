#include "tree.h"

Tree::Tree(Board *b){
    root = new Node(b, -1);
}

Tree::~Tree(){
    delete root;
}


void Tree::backTracking(Board* objective){
    Node current(root->board, -1);
    Node *root_copy = &current;

    while(current.board != objective){

    }

}
