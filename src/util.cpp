#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

    int getMatrixToArrayIndex(std::pair<int, int> pos, int column_size){
        return pos.first*column_size + pos.second;
    }

    std::pair<int, int> getArrayToMatrixIndex(int pos, int column_size){
        std::pair<int, int> matrix_pos;
        matrix_pos.first = pos / column_size;
        matrix_pos.second = pos % column_size;
        return matrix_pos;
    }

    bool contains(std::vector<int> v, int element){
        if(std::find(v.begin(), v.end(), element) != v.end()) {
            return true;
        } else {
            return false;
        }
    }

    bool contains(std::vector<std::vector<int> > v, std::vector<int> element){
        if(std::find(v.begin(), v.end(), element) != v.end()) {
            return true;
        } else {
            return false;
        }
    }

}
