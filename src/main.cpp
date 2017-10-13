#include <iostream>
#include <util.h>
#include <board.h>
#include <solver.h>
#include <stats.h>
#include <getopt.h>
#include <stdio.h>  /* EOF */
#include <stdlib.h> /* atoi */
#include "table_printer.h"

using namespace util;
using namespace std;

void usage(){
    cout << endl << "usuage: ./n-puzzle [options]" << endl;
    cout << endl << "\tOptions:" << endl;
    cout << "\t-s Size: length and width of board in blocks" << endl;
    cout << "\t-m Movements: number of movements to randomize initial board position" << endl;
    cout << "\t-h Help: print this message" << endl;
    cout << endl;
}

int main(int argc, char *argv[]){

    int opt, s = 3, m = 10;
    while ((opt = getopt(argc,argv,"hs:m:")) != EOF)
    switch(opt)
    {
        case 's':
            s = atoi(optarg);
            break;

        case 'm':
            m = atoi(optarg);
            break;

        default:
        case 'h':
            usage();
            return -1;

    }

    cout << "Board size set to " << s << "." << endl;
    cout << "Perfoming " << m << " randomized moves over initial position." << endl;

    Board myBoard(s*s);
    Board objectiveBoard(s*s);

    myBoard.randomizeBoard(m);

    cout << endl << "Generated board: " << endl;
    myBoard.printBoard();
    cout << endl;

    Solver solver(&myBoard);

    ExecutionStats* bfs = solver.BFS(&objectiveBoard);
    ExecutionStats* dfs = solver.DFS(&objectiveBoard);
    ExecutionStats* uniform = solver.uniformCostSearch(&objectiveBoard);
    ExecutionStats* greedy = solver.greedySearch(&objectiveBoard);
    ExecutionStats* a = solver.aStar(&objectiveBoard);
    ExecutionStats* ida = solver.idaStar(&objectiveBoard);

    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Method", 10);
    tp.AddColumn("Depth", 8);
    tp.AddColumn("Expanded", 10);
    tp.AddColumn("Branching Factor", 18);
    tp.AddColumn("Execution Time", 15);

    tp.PrintHeader();
    bfs->print(&tp);
    dfs->print(&tp);
    uniform->print(&tp);
    greedy->print(&tp);
    a->print(&tp);
    ida->print(&tp);
    tp.PrintFooter();

    delete bfs;
    delete dfs;
    delete uniform;
    delete greedy;
    delete a;
    delete ida;
}
