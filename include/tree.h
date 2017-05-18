#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <board.h>
#include <node.h>

class Tree{
    public:
        Tree(Board* b);
        ~Tree();

        void backTracking(Board* objective);

    private:
        Node* root;

};

#endif // TREE_H_INCLUDED
