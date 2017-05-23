#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <vector>

#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3

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
        bool doMove(int move);
        std::vector<int> availableMoves();
};

#endif // BOARD_H_INCLUDED
