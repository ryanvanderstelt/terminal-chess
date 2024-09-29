#include <iostream>
#include <vector>
#include <algorithm>
#include "piece.h"

using namespace std;

void printSquare(Piece **board, int loc, vector<int> moves = {})
{

    string rook[2] = {"\u2656", "\u265C"};
    string knight[2] = {"\u2658", "\u265E"};
    string bishop[2] = {"\u2657", "\u265D"};
    string queen[2] = {"\u2655", "\u265B"};
    string king[2] = {"\u2654", "\u265A"};
    string pawn[2] = {"\u2659", "\u265F"};

    bool white_square = (loc + loc / 8 + 1) % 2 == 0;

    if (count(moves.begin(), moves.end(), loc) > 0)
    {
        cout << "\033[46m";
        if (isupper(board[loc]->type))
        {
            white_square = 0;
            cout << "\033[37m";
        }
        else
        {
            white_square = 1;
            cout << "\033[30m";
        }
    }
    else if (white_square)
    {
        cout << "\033[30;47m";
    }
    else
    {
        cout << "\033[37;40m";
    }
    if (!board[loc])
    {
        cout << "   ";
        return;
    }
    switch (board[loc]->type)
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
        break;
    }
}

void printBoard(Piece **board, bool pov_white, vector<int> moves = {})
{
    if (pov_white)
    {
        for (int i = 7; i > -1; i--)
        {
            for (int j = 0; j < 8; j++)
            {
                if (j == 0)
                {
                    cout << "\033[0m" << endl
                         << ' ' << i + 1 << ' ';
                }
                printSquare(board, 8 * i + j, moves);
            }
        }
        cout << "\033[0m" << endl
             << "    a  b  c  d  e  f  g  h" << endl;
        }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 7; j > -1; j--)
            {
                if (j == 7)
                {
                    cout << "\033[0m" << endl
                         << ' ' << i + 1 << ' ';
                }
                printSquare(board, 8 * i + j, moves);
            }
        }
        cout << "\033[0m" << endl
             << "    h  g  f  e  d  c  b  a" << endl;
    }
}