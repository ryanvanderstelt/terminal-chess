#include <iostream>
#include <vector>

using namespace std;

struct Board
{

    char board[64];
    bool isWhite;

    Board();
    Board(Board &old_board);

    bool inCheck(int loc, char *board);

    vector<int> listMoves(int loc);
    void addMove(vector<int> &moves, int row, int col);
    void lineMoves(vector<int> &moves, int loc, int d_row, int d_col);

    void rMoves(vector<int> &moves, int loc);
    void bMoves(vector<int> &moves, int loc);
    void qMoves(vector<int> &moves, int loc);
    void nMoves(vector<int> &moves, int loc);
    void pMoves(vector<int> &moves, int loc);
    void kMoves(vector<int> &moves, int loc);
};

Board::Board()
{
    isWhite = true;
    for (int i = 0; i < 16; i++)
    {
        switch (i)
        {
        case 0:
        case 7:
            board[i] = 'R';
            board[56 + i] = 'r';
            break;

        case 1:
        case 6:
            board[i] = 'N';
            board[56 + i] = 'n';
            break;

        case 2:
        case 5:
            board[i] = 'B';
            board[56 + i] = 'b';
            break;

        case 3:
            board[i] = 'Q';
            board[56 + i] = 'q';
            break;

        case 4:
            board[i] = 'K';
            board[56 + i] = 'k';
            break;

        default:
            board[i] = 'P';
            board[63 - i] = 'p';
            break;
        }
    }
    for (int i = 16; i < 48; i++)
    {
        board[i] = '0';
    }
}

Board::Board(Board &old_board)
{
    for (int i = 0; i < 64; i++)
    {
        board[i] = old_board.board[i];
    }
    isWhite = old_board.isWhite;
}

vector<int> Board::listMoves(int loc)
{
    vector<int> moves_list;

    switch (tolower(board[loc]))
    {
    case 'r':
        rMoves(moves_list, loc);
        break;
    case 'n':
        nMoves(moves_list, loc);
        break;
    case 'b':
        bMoves(moves_list, loc);
        break;
    case 'q':
        qMoves(moves_list, loc);
        break;
    case 'k':
        kMoves(moves_list, loc);
        break;
    case 'p':
        pMoves(moves_list, loc);
        break;
    default:
        break;
    }
    return moves_list;
}

bool Board::inCheck(int loc, char *board)
{
    return false;
}

void Board::addMove(vector<int> &moves, int row, int col)
{
    int loc = row * 8 + col;
    if (row < 8 && row > -1 && col < 8 && col > -1 && !inCheck(loc, board))
    {
        if (board[loc] != '0' && (isupper(board[loc]) > 0 == isWhite))
        {
            return;
        }
        moves.push_back(loc);
    }
}

void Board::lineMoves(vector<int> &moves, int loc, int d_row, int d_col)
{
    int row = loc / 8 + d_row;
    int col = loc % 8 + d_col;

    while (row < 8 && row > -1 && col < 8 && col > -1 && board[8 * row + col] == '0')
    {
        addMove(moves, row, col);
        row += d_row;
        col += d_col;
    }
    if (board[8 * row + col] != '0' && (isupper(board[8 * row + col]) > 0 != isWhite))
    {
        addMove(moves, row, col);
    }
}

void Board::rMoves(vector<int> &moves, int loc)
{
    lineMoves(moves, loc, 1, 0);
    lineMoves(moves, loc, -1, 0);
    lineMoves(moves, loc, 0, 1);
    lineMoves(moves, loc, 0, -1);
}

void Board::bMoves(vector<int> &moves, int loc)
{
    lineMoves(moves, loc, 1, 1);
    lineMoves(moves, loc, 1, -1);
    lineMoves(moves, loc, -1, 1);
    lineMoves(moves, loc, -1, -1);
}

void Board::qMoves(vector<int> &moves, int loc)
{
    rMoves(moves, loc);
    bMoves(moves, loc);
}

void Board::nMoves(vector<int> &moves, int loc)
{
    int row = loc / 8;
    int col = loc % 8;
    addMove(moves, row + 2, col + 1);
    addMove(moves, row - 2, col + 1);
    addMove(moves, row + 2, col - 1);
    addMove(moves, row - 2, col - 1);
    addMove(moves, row + 1, col + 2);
    addMove(moves, row - 1, col + 2);
    addMove(moves, row + 1, col - 2);
    addMove(moves, row - 1, col - 2);
}

void Board::pMoves(vector<int> &moves, int loc)
{
}

void Board::kMoves(vector<int> &moves, int loc)
{
}
// void Board::addMove(vector<int> &moves, int loc, int col, int row, bool addLine)
// {
//     int mv_coord = loc + 8 * row + col;

//     if (loc / 8 + row < 0 || loc / 8 + row > 7 || loc % 8 + col < 0 || loc % 8 + col > 7 || (isupper(board[mv_coord]->type) && isWhite))
//     {
//         return;
//     }
//     else
//     {
//         moves.push_back(mv_coord);
//         if (addLine)
//         {
//             addMove(moves, mv_coord, col, row, addLine);
//         }
//     }
// }