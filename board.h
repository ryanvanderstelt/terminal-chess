#include "piece.h"
#pragma once

using namespace std;

struct Board
{

    Piece **board;

    Board();
    Board(Piece **copy_board);
    ~Board();

    bool inCheck(bool isWhite);
    bool isCheckmate(bool isWhitesTurn);
    vector<int> listMoves(int loc);
};

Board::Board()
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

Board::Board(Piece **copy_board)
{
    for (int i = 0; i < 63; i++)
    {
        board[i] = copy_board[i];
    }
}

Board::~Board()
{
    for (int i = 0; i < 63; i++)
    {
        delete board[i];
    }
    delete[] board;
}
bool Board::inCheck(bool isWhite)
{
    return false;
}
bool Board::isCheckmate(bool isWhitesTurn)
{
    return false;
}

vector<int> Board::listMoves(int loc)
{
    vector<int> moves_list;
    Board copy_board(board);
    copy_board.board[loc] = nullptr;

    if (copy_board.inCheck(isupper(board[loc]->type)))
    {
        return moves_list;
    }
    switch (tolower(board[loc]->type))
    {
    case 'r':
        // check up until piece
        //      add to moves_list
        // check down until piece
        //      add to moves_list
        // check right until piece
        //      add to moves_list
        // check left until piece
        //      add to moves_list
        break;
    case 'n':
        // check in circle by adding
        break;
    case 'b':
        // check NE until piece
        //      add to moves_list
        // check SE until piece
        //      add to moves_list
        // check SW until piece
        //      add to moves_list
        // check NW until piece
        //      add to moves_list
        break;
    case 'q':
        // check b and r
        //      add to moves_list
        break;
    case 'k':
        // check all adjacent moves
        //      add to moves_list
        // check castling
        //      add to moves_list
        break;
    case 'p':
        // check spot in front for piece
        //      add to moves_list
        // check front diagnols for pieces
        //      add to moves_list
        // check if adjacent pieces passantable
        //      add to moves_list
        // if promotion, receive input and change piece type
        break;
    default:
        break;
    }
    return moves_list;
}

// vector<int> addLine(Board board, bool isWhite, int col, int row)
// {
//     int mv_coord = 8 * row + col;
//     vector<int> line_moves;
//     while (true) {
//         if (col < 7 && col > 0 && row < 7 && row > 0 && isupper(board.board[mv_coord]->type) == isWhite)
//     {
//         return line_moves;
//     }
//     else if (isupper(board.board[mv_coord]->type) != isWhite)
//     {
//         return line_moves;
//     }
//     }
// }

// vector<int> addMove(Board board, bool isWhite, int loc, int col, int row)
// {
//     int mv_coord = 8 * row + col;
//     if (col < 0 || col > 7 || row < 0 || row > 7 || isupper(board.board[mv_coord]->type) == isWhite)
//     {
//         return {};
//     }
//     else if (isupper(board.board[mv_coord]->type) != isWhite)
//     {
//         return mv_coord;
//     }
// }
