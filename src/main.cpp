#include <iostream>
#include <util.h>
#include <board.h>
#include <tree.h>
#include <getopt.h>
#include <stdio.h>  /* EOF */
#include <stdlib.h> /* atoi */

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

    cout << endl << "Objective board: " << endl;
    objectiveBoard.printBoard();
    cout << endl;

    Tree t(&myBoard);

    cout << "============================= " << endl;
    cout << "         Backtracking         " << endl;
    cout << "============================= " << endl;
    if(m < 25)
        t.backTracking(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "             BFS              " << endl;
    cout << "============================= " << endl;
    t.BFS(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "             DFS              " << endl;
    cout << "============================= " << endl;
    t.DFS(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "      Uniform Cost Search     " << endl;
    cout << "============================= " << endl;
    t.uniformCostSearch(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "        Greedy Search         " << endl;
    cout << "============================= " << endl;
    t.greedySearch(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "             A*               " << endl;
    cout << "============================= " << endl;
    t.aStar(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "            IDA*              " << endl;
    cout << "============================= " << endl;
    t.idaStar(&objectiveBoard);
    cout << "----------------------------- " << endl << endl;

}
