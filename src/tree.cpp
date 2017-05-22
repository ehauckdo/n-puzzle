#include "tree.h"

Tree::Tree(Board *b){
    root = new Node(b, -1);
}

Tree::~Tree(){
    delete root;
}


void Tree::backTracking(Board* objective){

}
