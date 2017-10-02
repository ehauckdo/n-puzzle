#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

class ExecutionStats{
    public:
        ExecutionStats();
        ExecutionStats(int d, int e, int v, float b, float t);
        void print();
        ~ExecutionStats();

        int depth;
        int expanded;
        int visited;
        float branchingFactor;
        float executionTime;
};

#endif // STATS_H_INCLUDED
