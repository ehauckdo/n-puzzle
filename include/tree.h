#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <board.h>
#include <node.h>


class Tree{
    public:
        Tree(Board* b);
        ~Tree();

        void backTracking(Board* objective);
        void DFS(Board* objective, int limit = 25);
        void BFS(Board* objective);
        void uniformCostSearch(Board* objective);
        void greedySearch(Board* objective);
        void aStar(Board* objective);
        void idaStar(Board* objective);

        void printPath(Node* leaf);

    //private:
        Node* root;

};

#endif // TREE_H_INCLUDED
