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

}
