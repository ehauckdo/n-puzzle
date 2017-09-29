#include <iostream>
#include <util.h>
#include <board.h>
#include <tree.h>

using namespace util;
using namespace std;

int main(int argc, char *argv[]){

    cout << argc << endl;
    for(int i = 0; i < argc; i++){
        cout << argv[i] << endl;
    }

    int k = 0;
    cout << "=================================================" << endl;
    cout << "                  N-PUZZLE SOLVER                " << endl;
    cout << "=================================================" << endl;
    cout << endl;

    cout << "Type the number of rows/columns of your puzzle (recommended: 3): ";
    while((k = getInputInt()) <= 0){
        cout << "Invalid input. Please, insert a valid number: ";
    }

    Board b(k*k);
    Board b2(&b);

    cout << "Type a number of movements to randomize the board (recommended: 10~20): ";
    while((k = getInputInt()) <= 0){
        cout << "Invalid input. Please, insert a valid number: ";
    }

    b2.randomizeBoard(k);

    cout << endl << "Generated board: " << endl;
    b.printBoard();
    cout << endl;

    cout << endl << "Objective board: " << endl;
    b2.printBoard();
    cout << endl;

    Tree t(&b);

    cout << "============================= " << endl;
    cout << "         Backtracking         " << endl;
    cout << "============================= " << endl;
    if(k < 25)
        t.backTracking(&b2);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "             BFS              " << endl;
    cout << "============================= " << endl;
    t.BFS(&b2);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "             DFS              " << endl;
    cout << "============================= " << endl;
    t.DFS(&b2);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "      Uniform Cost Search     " << endl;
    cout << "============================= " << endl;
    t.uniformCostSearch(&b2);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "        Greedy Search         " << endl;
    cout << "============================= " << endl;
    t.greedySearch(&b2);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "             A*               " << endl;
    cout << "============================= " << endl;
    t.aStar(&b2);
    cout << "----------------------------- " << endl << endl;

    cout << "============================= " << endl;
    cout << "            IDA*              " << endl;
    cout << "============================= " << endl;
    t.idaStar(&b2);
    cout << "----------------------------- " << endl << endl;

}
