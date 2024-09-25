#include <iostream>

using namespace std;


//how to store info (class/struct)
//
//how to iterate through pieces (list, array, etc)
//maybe just array with coords math (smart, simple)
//
//functions are trivial, just need to know how to manage data
//
//devins bit idea for castle memory (maybe)



class Piece {
    public:
        char type;
        int col;
        int row;
        int moves;
        bool moved;
        bool passantable;

        int* listMoves() {
            return;
        }
};

class Board {
    Piece board[64];
    void printBoard() {
        return;
    }
};

int main() {

}
