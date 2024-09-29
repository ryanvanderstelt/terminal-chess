#include <iostream>
#include <vector>
#pragma once

using namespace std;

struct Piece
{
public:
    char type;
    int col;
    int row;
    bool moved = false;
    bool passantable = false;

    Piece()
    {
    }
    Piece(char piece_type, int location)
    {
        type = piece_type;
        col = location % 8;
        row = location / 8;
    }
    vector<int> listMoves(Piece **board);
};

vector<int> Piece::listMoves(Piece **board)
{
    vector<int> moves_list;
    switch (tolower(type))
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