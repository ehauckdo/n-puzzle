#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <board.h>

class Node{
    public:
        Node(Board* b);
        ~Node();

        Board* board;

};

#endif // NODE_H_INCLUDED
