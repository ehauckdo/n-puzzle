#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED
#include <board.h>
#include <node.h>
#include <stats.h>

class Solver{
    public:
        Solver(Board* b);
        ~Solver();

        ExecutionStats* backTracking(Board* objective);
        ExecutionStats* DFS(Board* objective, int limit = 25);
        ExecutionStats* BFS(Board* objective);
        ExecutionStats* uniformCostSearch(Board* objective);
        ExecutionStats* greedySearch(Board* objective);
        ExecutionStats* aStar(Board* objective);
        ExecutionStats* idaStar(Board* objective);

        void printPath(Node* leaf);
        Node* root;

};

#endif // SOLVER_H_INCLUDED
