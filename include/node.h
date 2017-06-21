#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <board.h>
#include <vector>

class Node{
    public:
        Node(Node* parent, Board* b, int executedMove);
        ~Node();

        Board* board;
        Node* parent;
        int id;
        int depth;
        int lastMove;
        std::vector<Node*> children;
        Node* expand(int move);
        Node* expand();
        bool isfullyExpanded();
        bool isAncestral(Board* b);
        std::vector<int> availableMoves;

        static int id_counter;
};

#endif // NODE_H_INCLUDED
