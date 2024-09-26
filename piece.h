#include <iostream>

using namespace std;

struct Piece
{
public:
    char type;
    int col;
    int row;
    bool moved = false;
    bool passantable = false;

    Piece() {
    };
    Piece(char piece_type, int location)
    {
        type = piece_type;
        col = location % 8;
        row = location / 8;
    }
};