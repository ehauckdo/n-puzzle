#include <string>
#include <iostream>
#include <math.h>
#include <util.h>
#include <unistd.h>
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
    cout << "                     N-PUZZLE"                     << endl;
    cout << "=================================================" << endl;
    cout << endl;

    cout << "Digite o tamanho do tabuleiro: ";

    while((k = getInputInt()) <= 0){
        cout << "Tamanho inválido. Por favor, digite um tamanho válido: ";
    }
    cout << "Tamanho escolhido: " << k << endl;

    Board b(k*k);
    Board b2(k*k);

    cout << endl << "Tabuleiro gerado: " << endl;
    b.printBoard();
    cout << endl;

    cout << "MENU DE OPÇÕES"    << endl;
    cout << "1 - Backtracking"  << endl;
    cout << "2 - Largura"       << endl;
    cout << "3 - Profundidade"  << endl;
    cout << "4 - Ordenada"      << endl;
    cout << "5 - Gulosa"        << endl;
    cout << "6 - A*"            << endl;
    cout << "7 - IDA*"          << endl;

    cout << b.availableMoves() << endl;

}
