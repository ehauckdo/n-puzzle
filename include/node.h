#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <board.h>
#include <vector>

class Node{
    public:
        Node(Board* b, int executedMove);
        ~Node();

        Board* board;
        int lastMove;
        std::vector<Node*> children;
        bool expand(int move);
        bool isfullyExpanded();

};

#endif // NODE_H_INCLUDED
