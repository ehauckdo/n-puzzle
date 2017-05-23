#include <vector>

namespace util{

    int getInputInt();
    std::string getInputString();
    int getMatrixToArrayIndex(std::pair<int, int> pos, int column_size);
    std::pair<int, int> getArrayToMatrixIndex(int pos, int column_size);
    bool contains(std::vector<int> v, int element);
}
