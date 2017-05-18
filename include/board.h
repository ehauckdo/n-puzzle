#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

class Board{
    public:
        int* board;
        int current_pos;
        int board_size;
        void copyFromBoard(Board* b);

        Board(const int size);
        Board(Board *b);
        ~Board();

        void printBoard();
        void randomizeBoard();
        void resetBoard();
        int availableMoves();
};

#endif // BOARD_H_INCLUDED
