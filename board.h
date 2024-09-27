#include "piece.h"

using namespace std;

void initializeBoard(Piece **&board)
{
    board = new Piece *[64];
    for (int i = 0; i < 16; i++)
    {
        switch (i)
        {
        case 0:
        case 7:
            board[i] = new Piece('r', i);
            board[56 + i] = new Piece('R', 56 + i);
            break;

        case 1:
        case 6:
            board[i] = new Piece('n', i);
            board[56 + i] = new Piece('N', 56 + i);
            break;

        case 2:
        case 5:
            board[i] = new Piece('b', i);
            board[56 + i] = new Piece('B', 56 + i);
            break;

        case 3:
            board[i] = new Piece('q', i);
            board[56 + i] = new Piece('Q', 56 + i);
            break;

        case 4:
            board[i] = new Piece('k', i);
            board[56 + i] = new Piece('K', 56 + i);
            break;

        default:
            board[i] = new Piece('p', i);
            board[63 - i] = new Piece('P', 63 - i);
            break;
        }
    }
}
void destroyBoard(Piece **&board)
{
    for (int i = 0; i < 63; i++)
    {
        delete board[i];
    }
    delete[] board;
}