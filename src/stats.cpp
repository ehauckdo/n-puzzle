#include "stats.h"
#include <iostream>

ExecutionStats::ExecutionStats(){
}

ExecutionStats::ExecutionStats(int d, int e, int v, float b, float t){
    this->depth = d;
    this->expanded = e;
    this->visited = v;
    this->branchingFactor = b;
    this->executionTime = t;
}

void ExecutionStats::print(){
    std::cout << "Depth of solution: " << this->depth << std::endl;
    std::cout << "Expanded nodes: " << this->expanded << std::endl;
    std::cout << "Visited nodes: " << this->visited << std::endl;
    std::cout << "Branching factor: " << this->branchingFactor << std::endl;
    std::cout << "Execution time: " << this->executionTime << std::endl;
}

ExecutionStats::~ExecutionStats(){
}
