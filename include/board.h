#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <vector>

#define MOVE_LEFT 0
#define MOVE_RIGHT 1
#define MOVE_UP 2
#define MOVE_DOWN 3



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
        bool isSolvable(Board* target);

    private:
        int getInversionCount(Board* target);
};

#endif // BOARD_H_INCLUDED
