#include <iostream>
#include <vector>
#include <algorithm>
#include "piece.h"
#include "print.h"
#include "board.h"

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

int main()
{
    Piece **board;
    bool isWhitesTurn = true;

    initializeBoard(board);
    printBoard(board, isWhitesTurn);
    cout << "Welcome to Terminal Chess!" << endl;
    while (true)
    {
        int coord;
        bool validMove = false;

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
            char col_row[2];
            vector<int> moves_list;
            vector<int> print_list;
            while (true)
            {
                cout << "Enter coord of piece: ";
                cin >> col_row;
                coord = (col_row[0] - 'a') + 8 * (col_row[1] - '1');
                if (coord > -1 && coord < 64 && board[coord] && (islower(board[coord]->type) > 0) != isWhitesTurn)
                {
                    cout << board[coord]->type << endl
                         << islower(board[coord]->type) << endl;
                    break;
                }
            }

            print_list.push_back(coord);
            moves_list = board[coord]->listMoves(board);
            print_list.insert(moves_list.end(), moves_list.begin(), moves_list.end());

            printBoard(board, isWhitesTurn, print_list);
            cout << endl
                 << "Enter coord of destination: ";
            cin >> col_row;
            //
            // See if coord is a valid move for selected piece
            // If selected move is an ally, treat it as the selected piece
            //
            validMove = true;
        }
        //
        // Execute move  !!!FIGURE OUT EN PASSANT!!!
        // See if check
        // If check, see if checkmate
        // If checkmate, exit loop and print final board (maybe move history as a later feature)
        //
        isWhitesTurn = !isWhitesTurn;
        printBoard(board, isWhitesTurn);
    }
    printBoard(board, isWhitesTurn);
    if (isWhitesTurn)
    {
        cout << "White Wins!";
    }
    else
    {
        cout << "Black Wins!";
    }
    destroyBoard(board);
}
