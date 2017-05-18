#include "tree.h"

Tree::Tree(Board *b){
    root = new Node(b);
}

Tree::~Tree(){
    delete root;
}


void Tree::backTracking(Board* objective){

}
