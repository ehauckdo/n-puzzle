#include "node.h"


Node::Node(Board* b){
    board = new Board(b);

    // reserve enough space for children nodes
    children.reserve(b->availableMoves());
}

Node::~Node(){

}
