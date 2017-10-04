#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED
#include "table_printer.h"

class ExecutionStats{
    public:
        ExecutionStats();
        ExecutionStats(std::string m, int d, int e, int v, float b, float t);
        void print();
        void print(bprinter::TablePrinter* tp);
        ~ExecutionStats();

        std::string method;
        int depth;
        int expanded;
        int visited;
        float branchingFactor;
        float executionTime;
};

#endif // STATS_H_INCLUDED
