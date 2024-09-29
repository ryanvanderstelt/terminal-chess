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
            board[i] = new Piece('R', i);
            board[56 + i] = new Piece('r', 56 + i);
            break;

        case 1:
        case 6:
            board[i] = new Piece('N', i);
            board[56 + i] = new Piece('n', 56 + i);
            break;

        case 2:
        case 5:
            board[i] = new Piece('B', i);
            board[56 + i] = new Piece('b', 56 + i);
            break;

        case 3:
            board[i] = new Piece('Q', i);
            board[56 + i] = new Piece('q', 56 + i);
            break;

        case 4:
            board[i] = new Piece('K', i);
            board[56 + i] = new Piece('k', 56 + i);
            break;

        default:
            board[i] = new Piece('P', i);
            board[63 - i] = new Piece('p', 63 - i);
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
bool isCheck(Piece **board, bool isWhitesTurn)
{
}
bool isCheckmate(Piece **board, bool isWhitesTurn)
{
}