#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include <board.h>
#include <node.h>
#include <stats.h>

class Tree{
    public:
        Tree(Board* b);
        ~Tree();

        ExecutionStats* backTracking(Board* objective);
        ExecutionStats* DFS(Board* objective, int limit = 25);
        ExecutionStats* BFS(Board* objective);
        ExecutionStats* uniformCostSearch(Board* objective);
        ExecutionStats* greedySearch(Board* objective);
        ExecutionStats* aStar(Board* objective);
        ExecutionStats* idaStar(Board* objective);

        void printPath(Node* leaf);

    //private:
        Node* root;

};

#endif // TREE_H_INCLUDED
