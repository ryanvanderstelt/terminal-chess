#include <iostream>
#include <vector>
#include <algorithm>
#include "print.h"

using namespace std;

// devins bit idea for castle memory (maybe)
// think about a handleInput function
// think about a function that returns a list of moves in a line (diagnols too)
// think about refactoring board into a proper struct with functions

/*

Game Plan:

1. Initialize game
2. User input for piece
    a. Check if location given holds one of the active players pieces.
    b. Translate from chess jargon to zero-indexed column and row (e8 == 4, 7)
3. List moves for piece
    a. Check if in bounds
    b. Check if lands on ally
    c. Check if active player will be in check
    d. Display options
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
    Board board;

    cout << "Welcome to Terminal Chess!" << endl;
    while (true)
    {
        int loc_piece;
        int loc_move;
        bool validMove = false;

        while (!validMove)
        {
            char col_row[2];
            vector<int> moves_list;
            vector<int> print_list;
            moves_list.reserve(3);
            print_list.reserve(3);
            while (true)
            {
                cout << endl;
                printBoard(board);
                if (board.isWhite)
                {
                    cout << "White's Turn!" << endl;
                }
                else
                {
                    cout << "Black's Turn!" << endl;
                }
                cout << "Enter coord of piece: ";
                cin >> col_row;
                loc_piece = (col_row[0] - 'a') + 8 * (col_row[1] - '1');
                if (loc_piece > -1 && loc_piece < 64 && board.board[loc_piece] != '0' && (islower(board.board[loc_piece]) > 0) != board.isWhite)
                {
                    break;
                }
            }

            print_list.push_back(loc_piece);
            moves_list = board.listMoves(loc_piece);
            print_list.insert(print_list.end(), moves_list.begin(), moves_list.end());

            cout << endl;
            printBoard(board, print_list);
            cout << endl
                 << "Enter coord of destination: ";
            cin >> col_row;
            //
            // See if coord is a valid move for selected piece
            // If selected move is an ally, treat it as the selected piece
            // may have to create temporary boards to see if king is in check
            // OR just one temp board without selected piece (smart maybe)
            //
            loc_move = (col_row[0] - 'a') + (col_row[1] - '1') * 8;
            while (!moves_list.empty())
            {
                if (moves_list.back() == loc_move)
                {
                    validMove = true;
                    break;
                }
                moves_list.pop_back();
            }
            moves_list.clear();
            print_list.clear();
        }
        board.board[loc_move] = board.board[loc_piece];
        board.board[loc_piece] = '0';
        if (board.isWhite)
        {
            board.b_ep = -1;
        }
        else
        {
            board.w_ep = -1;
        }

        board.isWhite = !board.isWhite;
    }
    printBoard(board);
    if (board.isWhite)
    {
        cout << "White Wins!";
    }
    else
    {
        cout << "Black Wins!";
    }
}
