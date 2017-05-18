#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <vector>

class Board{
    public:
        std::vector<int> board;
        int current_pos;
        int board_size;

        Board(const int size);
        Board(Board *b);
        ~Board();

        void printBoard();
        void randomizeBoard();
        void resetBoard();
        int availableMoves();
};

#endif // BOARD_H_INCLUDED
