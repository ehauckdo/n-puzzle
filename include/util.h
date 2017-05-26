#include <vector>
#include <string>

namespace util{

    int getInputInt();
    std::string getInputString();
    int getMatrixToArrayIndex(std::pair<int, int> pos, int column_size);
    std::pair<int, int> getArrayToMatrixIndex(int pos, int column_size);
    bool contains(std::vector<int> v, int element);
    bool contains(std::vector<std::vector<int> > v, std::vector<int> element);
    int find(std::vector<int> v, int element);
}
