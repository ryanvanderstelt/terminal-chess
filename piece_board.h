#include <iostream>

using namespace std;

// struct Move {
//     int moveFrom;
//     int moveTo;
// };

class Piece {
    public:
        char type;
        int col;
        int row;
        bool moved = false;
        bool passantable = false;

        Piece() {
        };
        Piece(char piece_type, int location) {
            type = piece_type;
            col = location % 8;
            row = location / 8;
        }
        // Move* listMoves() {
        //     return;
        // }
};

// struct Player {
//     Piece pieces[16];
//     Move moveList[];
// };

class Board {
    public:
        Piece* board;
        Board() {
            board = new Piece[64];
            for (int i = 0; i < 16; i++) {
                switch (i)
                {
                case 0: case 7:
                    board[i] = Piece('r', i);
                    board[56 + i] = Piece('R', 56 + i);
                    break;

                case 1: case 6:
                    board[i] = Piece('n', i);
                    board[56 + i] = Piece('N', 56 + i);
                    break;

                case 2: case 5:
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
        void printBoard() {
            for (int i=0; i<64; i++) {
                if (i % 8 == 0) {
                    cout << endl;
                }
                if (board[i].type) {
                    cout << board[i].type;
                } else {
                    cout << ' ';
                }
            }
            cout << endl;    
        }
};