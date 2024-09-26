#include <iostream>
#include "piece_board.h"

using namespace std;

// devins bit idea for castle memory (maybe)

/*

Game Plan:

1. Initialize game
2. User input for piece
    a. Check if location given holds one of the active players pieces.
    b. Translate from chess jargon to zero-indexed column and row (e8 == 4, 7)
3. List moves for piece
    a. Check if in bounds
    b. Check if lands on ally
    b. Check if active player will be in check
    c. Display options
4. User input for destination
    a. Any invalid move unfocuses piece (go back to step 2)
5. Move piece to destination
6. Evaluate board
    a. If enemy is in check, check for checkmate
        1. If checkmate, end game
        2. If not checkmate, alert of check
7. Swap player and go back to step 2

*/

void initializeBoard(Piece *&board);

void printBoard(Piece *&board);

int main()
{
    Piece *board;
    bool not_checkmate = true;

    initializeBoard(board);
    printBoard(board);
    cout << "Welcome to Terminal Chess!\nType the coordinate of the piece you want to move to get started: " << endl;
    // while (not_checkmate) {

    // }
}

void initializeBoard(Piece *&board)
{
    board = new Piece[64];
    for (int i = 0; i < 16; i++)
    {
        switch (i)
        {
        case 0:
        case 7:
            board[i] = Piece('r', i);
            board[56 + i] = Piece('R', 56 + i);
            break;

        case 1:
        case 6:
            board[i] = Piece('n', i);
            board[56 + i] = Piece('N', 56 + i);
            break;

        case 2:
        case 5:
            board[i] = Piece('b', i);
            board[56 + i] = Piece('B', 56 + i);
            break;

        case 3:
            board[i] = Piece('q', i);
            board[56 + i] = Piece('Q', 56 + i);
            break;

        case 4:
            board[i] = Piece('k', i);
            board[56 + i] = Piece('K', 56 + i);
            break;

        default:
            board[i] = Piece('p', i);
            board[63 - i] = Piece('P', 63 - i);
            break;
        }
    }
}

void printBoard(Piece *&board)
{
    string rook[2] = {"\u2656", "\u265C"};
    string knight[2] = {"\u2658", "\u265E"};
    string bishop[2] = {"\u2657", "\u265D"};
    string queen[2] = {"\u2655", "\u265B"};
    string king[2] = {"\u2654", "\u265A"};
    string pawn[2] = {"\u2659", "\u265F"};
    bool white_square;

    for (int i = 0; i < 64; i++)
    {
        white_square = (i + i / 8) % 2 == 0;
        if (i % 8 == 0)
        {
            cout << "\033[0m" << endl;
        }
        if (white_square)
        {
            cout << "\033[30;47m";
        }
        else
        {
            cout << "\033[37;40m";
        }
        switch (board[i].type)
        {
        case 'r':
            cout << ' ' << rook[white_square] << ' ';
            break;

        case 'n':
            cout << ' ' << knight[white_square] << ' ';
            break;

        case 'b':
            cout << ' ' << bishop[white_square] << ' ';
            break;

        case 'q':
            cout << ' ' << queen[white_square] << ' ';
            break;

        case 'k':
            cout << ' ' << king[white_square] << ' ';
            break;

        case 'p':
            cout << ' ' << pawn[white_square] << ' ';
            break;

        case 'R':
            cout << ' ' << rook[!white_square] << ' ';
            break;

        case 'N':
            cout << ' ' << knight[!white_square] << ' ';
            break;

        case 'B':
            cout << ' ' << bishop[!white_square] << ' ';
            break;

        case 'Q':
            cout << ' ' << queen[!white_square] << ' ';
            break;

        case 'K':
            cout << ' ' << king[!white_square] << ' ';
            break;

        case 'P':
            cout << ' ' << pawn[!white_square] << ' ';
            break;

        default:
            cout << "   ";
        }
    }
    cout << "\033[0m" << endl
         << endl;
}