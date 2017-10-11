#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <node.h>
#include <iomanip>

#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3

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

    int find(std::vector<int> v, int element){
        std::vector<int>::iterator it;

        it = find (v.begin(), v.end(), element);
        if (it != v.end())
            return std::distance(v.begin(), it);
        else
            return -1;
    }

    int getOppositeMove(int move){
        if(move == MOVE_UP)
            return MOVE_DOWN;
        else if(move == MOVE_DOWN)
            return MOVE_UP;
        else if(move == MOVE_LEFT)
            return MOVE_RIGHT;
        else if(move == MOVE_RIGHT)
            return MOVE_LEFT;
        else return -1;
    }

    std::string getMoveName(int move){
        switch(move){
            case MOVE_UP: return "MOVE_UP";
            case MOVE_DOWN: return "MOVE_DOWN";
            case MOVE_LEFT: return "MOVE_LEFT";
            case MOVE_RIGHT: return "MOVE_RIGHT";
            default: return "Invalido Move";
        }

    }

    std::string getMoveSymbol(int move){
        switch(move){
            case MOVE_UP: return "↑";
            case MOVE_DOWN: return "↓";
            case MOVE_LEFT: return "←";
            case MOVE_RIGHT: return "→";
            default: return "Invalido Move";
        }

    }

    void insertOrdered(Node* node, std::vector<Node*>* myvector, Board* objective){
        std::cout << "Current: " << node->board->getH2(objective) << std::endl;
        int initial_size = myvector->size();
        int i = 0;
        for(std::vector<Node*>::iterator it = myvector->begin(); it != myvector->end(); it++){
            if(node->board->getH2(objective) < (*it)->board->getH2(objective)){
                myvector->insert(it, node);
                std::cout << "Discarded at "<< i <<" position, H2: " << (*it)->board->getH2(objective) << std::endl;
                break;
            }
            i = i + 1;
        }

        if(myvector->size() == initial_size){
            if(initial_size != 0)
                std::cout << "Inserted at last ("<< i<<") position, H2: " << (*myvector)[initial_size-1]->board->getH2(objective) << std::endl;
            else
                std::cout << "Inserted at last ("<< i<<") position, H2: " << std::endl;
            myvector->push_back(node);
        }
    }

    std::string getDecimalPlaces(float number, int decimal_places){
        std::stringstream ss;
        ss << std::fixed << std::setprecision(decimal_places) << number;
        return ss.str();
    }

}
