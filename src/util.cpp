#include <string>
#include <iostream>
#include <sstream>

namespace util{

    int getInputInt(){
        int numero = 0;
        std::string input;
        getline (std::cin, input);
        std::stringstream(input) >> numero;
        return numero;
    }

    std::string getInputString(){
        std::string input;
        getline (std::cin, input);
        return input;
    }

    int getMatrixToArrayIndex(int row, int column, int column_size){
        return row*column_size + column;
    }

    std::pair<int, int> getArrayToMatrixIndex(int pos, int column_size){
        std::pair<int, int> matrix_pos;
        matrix_pos.first = pos / column_size;
        matrix_pos.second = pos % column_size;
        return matrix_pos;
    }

}
