#include <iostream>
#include <vector>
#include <algorithm>
#include "piece.h"

using namespace std;

// devins bit idea for castle memory (maybe)
// potentially refactor to array of pointers to Pieces

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

void printSquare(Piece *board, int loc, vector<int> moves = {});

void printBoard(Piece *board, bool pov_white, vector<int> moves = {});

int main()
{
    Piece *board;
    bool isWhitesTurn = true;
    bool validPiece;
    bool validMove;
    char col_row[2];
    int coord;

    initializeBoard(board);
    printBoard(board, isWhitesTurn);
    cout << "Welcome to Terminal Chess!" << endl;
    while (true)
    {
        validMove = false;
        if (isWhitesTurn)
        {
            cout << "White's Turn!" << endl;
        }
        else
        {
            cout << "Black's Turn!" << endl;
        }
        while (!validMove)
        {
            while (true)
            {
                cout << "Enter coord of piece: ";
                cin >> col_row;
                coord = 56 + (col_row[0] - 'a') - 8 * (col_row[1] - '1');
                if (islower(board[coord].type) != isWhitesTurn)
                {
                    break;
                }
            }
            vector<int> listMoves;
            //
            // List all possible moves for selected piece
            //
            printBoard(board, isWhitesTurn, listMoves); // should be changed to show a list of available moves as a seperate color
            cout << endl
                 << "Enter coord of destination: ";
            cin >> col_row;
            //
            // See if coord is a valid move for selected piece
            //
            validMove = true;
        }
        //
        // Execute move
        // See if check
        // If check, see if checkmate
        // If checkmate, exit loop and print final board (maybe move history as a later feature)
        //
        isWhitesTurn = !isWhitesTurn;
        printBoard(board, isWhitesTurn);
    }
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

void printBoard(Piece *board, bool pov_white, vector<int> moves)
{
    if (pov_white)
    {
        for (int i = 0; i < 64; i++)
        {
            if (i % 8 == 0)
            {
                cout << "\033[0m" << endl
                     << ' ' << 8 - i / 8 << ' ';
            }
            printSquare(board, i, moves);
        }
        cout << "\033[0m" << endl
             << "    a  b  c  d  e  f  g  h" << endl;
    }
    else
    {
        for (int i = 63; i > -1; i--)
        {
            if ((i + 1) % 8 == 0)
            {
                cout << "\033[0m" << endl
                     << ' ' << 8 - i / 8 << ' ';
            }
            printSquare(board, i, moves);
        }
        cout << "\033[0m" << endl
             << "    h  g  f  e  d  c  b  a" << endl;
    }
}

void printSquare(Piece *board, int loc, vector<int> moves)
{
    string rook[2] = {"\u2656", "\u265C"};
    string knight[2] = {"\u2658", "\u265E"};
    string bishop[2] = {"\u2657", "\u265D"};
    string queen[2] = {"\u2655", "\u265B"};
    string king[2] = {"\u2654", "\u265A"};
    string pawn[2] = {"\u2659", "\u265F"};

    bool white_square = (loc + loc / 8) % 2 == 0;

    if (count(moves.begin(), moves.end(), loc) > 0)
    {
        cout << "\033[46m";
        if (isupper(board[loc].type))
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
    switch (board[loc].type)
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