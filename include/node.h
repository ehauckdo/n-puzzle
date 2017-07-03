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
        static int id_counter;
        std::vector<Node*> children;
        std::vector<int> availableMoves;
        Node* expand(int move);
        Node* expand();
        bool isfullyExpanded();
        bool isAncestral(Board* b);
        int getChildren(Node* current_node, int num_children);

};

#endif // NODE_H_INCLUDED
