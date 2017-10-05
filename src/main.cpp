#include <iostream>
#include <util.h>
#include <board.h>
#include <tree.h>
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

    Tree t(&myBoard);

    if(m < 25)
        ExecutionStats* backtracking = t.backTracking(&objectiveBoard);

    ExecutionStats* bfs = t.BFS(&objectiveBoard);
    ExecutionStats* dfs = t.DFS(&objectiveBoard);
    ExecutionStats* uniform = t.uniformCostSearch(&objectiveBoard);
    ExecutionStats* greedy = t.greedySearch(&objectiveBoard);
    ExecutionStats* a = t.aStar(&objectiveBoard);
    ExecutionStats* ida = t.idaStar(&objectiveBoard);

    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Method", 10);
    tp.AddColumn("Depth", 10);
    tp.AddColumn("Expanded", 10);
    tp.AddColumn("Branch Factor", 10);
    tp.AddColumn("Execution Time", 10);

    tp.PrintHeader();
    bfs->print(&tp);
    dfs->print(&tp);
    uniform->print(&tp);
    greedy->print(&tp);
    a->print(&tp);
    ida->print(&tp);
    tp.PrintFooter();

}
