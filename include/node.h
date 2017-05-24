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
        bool expand();
        bool isfullyExpanded();
        std::vector<int> availableMoves;

};

#endif // NODE_H_INCLUDED
