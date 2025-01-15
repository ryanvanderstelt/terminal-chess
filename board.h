#include <iostream>
#include <vector>

using namespace std;

struct Board
{

    char board[64];
    bool isWhite;
    int w_king;
    int b_king;
    int b_ep;
    int w_ep;
    bool w_castle;
    bool w_qcastle;
    bool b_castle;
    bool b_qcastle;

    Board();
    Board(Board &old_board);

    bool inCheck(int loc);

    vector<int> listMoves(int loc);
    void addMove(vector<int> &moves, int origin, int row, int col);
    void lineMoves(vector<int> &moves, int origin, int loc, int d_row, int d_col);
    bool checkLine(int loc, int d_row, int d_col, char *pieces);
    bool spotCheck(int row, int col, char piece);

    void rMoves(vector<int> &moves, int loc);
    void bMoves(vector<int> &moves, int loc);
    void qMoves(vector<int> &moves, int loc);
    void nMoves(vector<int> &moves, int loc);
    void pMoves(vector<int> &moves, int loc);
    void kMoves(vector<int> &moves, int loc);
};

Board::Board()
{
    w_castle = true;
    w_qcastle = true;
    b_castle = true;
    b_qcastle = true;
    isWhite = true;
    b_ep = -1;
    w_ep = -1;
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
            w_king = i;
            b_king = 56 + i;
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
    w_king = old_board.w_king;
    b_king = old_board.b_king;
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

void Board::addMove(vector<int> &moves, int origin, int row, int col)
{
    int loc = row * 8 + col;
    if (row < 8 && row > -1 && col < 8 && col > -1)
    {
        Board temp_board(*this);
        temp_board.board[origin] = '0';
        if (isWhite)
        {
            temp_board.board[loc] = 'T';
            if (temp_board.inCheck(w_king))
            {
                return;
            }
        }
        else
        {
            temp_board.board[loc] = 't';
            if (temp_board.inCheck(b_king))
            {
                return;
            }
        }

        if (board[loc] != '0' && (isupper(board[loc]) > 0 == isWhite))
        {
            return;
        }
        moves.push_back(loc);
    }
}

void Board::lineMoves(vector<int> &moves, int origin, int loc, int d_row, int d_col)
{
    int row = loc / 8 + d_row;
    int col = loc % 8 + d_col;

    while (row < 8 && row > -1 && col < 8 && col > -1 && board[8 * row + col] == '0')
    {
        addMove(moves, origin, row, col);
        row += d_row;
        col += d_col;
    }
    if (board[8 * row + col] != '0' && (isupper(board[8 * row + col]) > 0 != isWhite))
    {
        addMove(moves, origin, row, col);
    }
}

bool Board::checkLine(int loc, int d_row, int d_col, char *pieces)
{
    int row = loc / 8 + d_row;
    int col = loc % 8 + d_col;

    if (d_row != 0 && d_col != 0)
    {
        if (d_row == 1 && isWhite)
        {
            if (board[loc] == 'p')
            {
                return true;
            }
        }
        else if (d_row == -1 && !isWhite)
        {
            if (board[loc] == 'P')
            {
                return true;
            }
        }
    }
    while (row < 8 && row > -1 && col < 8 && col > -1 && board[8 * row + col] == '0')
    {
        for (int i = 0; i < sizeof(pieces) / sizeof(pieces[0]); i++)
        {
            if (pieces[i] == board[loc])
            {
                return true;
            }
        }
        row += d_row;
        col += d_col;
    }
    return false;
}

bool Board::spotCheck(int row, int col, char piece)
{
    int loc = row * 8 + col;
    if (row < 8 && row > -1 && col < 8 && col > -1)
    {
        if (board[loc] == piece)
        {
            return true;
        }
    }
    return false;
}

bool Board::inCheck(int loc)
{
    char pieces[2] = {'r', 'q'};
    if (!isWhite)
    {
        toupper(pieces[0]);
        toupper(pieces[1]);
    }
    if (checkLine(loc, 1, 0, pieces) ||
        checkLine(loc, -1, 0, pieces) ||
        checkLine(loc, 0, 1, pieces) ||
        checkLine(loc, 0, -1, pieces))
    {
        return true;
    }

    pieces[0] = 'b';

    if (!isWhite)
    {
        toupper(pieces[0]);
    }
    if (checkLine(loc, 1, 1, pieces) ||
        checkLine(loc, 1, -1, pieces) ||
        checkLine(loc, -1, 1, pieces) ||
        checkLine(loc, -1, -1, pieces))
    {
        return true;
    }
    int row = loc / 8;
    int col = loc % 8;
    if (isWhite)
    {
        if (spotCheck(row + 2, col + 1, 'n') ||
            spotCheck(row - 2, col + 1, 'n') ||
            spotCheck(row + 2, col - 1, 'n') ||
            spotCheck(row - 2, col - 1, 'n') ||
            spotCheck(row + 1, col + 2, 'n') ||
            spotCheck(row - 1, col + 2, 'n') ||
            spotCheck(row + 1, col - 2, 'n') ||
            spotCheck(row - 1, col - 2, 'n'))
        {
            return true;
        }
        if (spotCheck(row + 1, col + 1, 'k') ||
            spotCheck(row + 1, col, 'k') ||
            spotCheck(row + 1, col - 1, 'k') ||
            spotCheck(row, col - 1, 'k') ||
            spotCheck(row - 1, col - 1, 'k') ||
            spotCheck(row - 1, col, 'k') ||
            spotCheck(row - 1, col + 1, 'k') ||
            spotCheck(row, col + 1, 'k'))
        {
            return true;
        }
    }
    else
    {
        if (spotCheck(row + 2, col + 1, 'N') ||
            spotCheck(row - 2, col + 1, 'N') ||
            spotCheck(row + 2, col - 1, 'N') ||
            spotCheck(row - 2, col - 1, 'N') ||
            spotCheck(row + 1, col + 2, 'N') ||
            spotCheck(row - 1, col + 2, 'N') ||
            spotCheck(row + 1, col - 2, 'N') ||
            spotCheck(row - 1, col - 2, 'N'))
        {
            return true;
        }
        if (spotCheck(row + 1, col + 1, 'K') ||
            spotCheck(row + 1, col, 'K') ||
            spotCheck(row + 1, col - 1, 'K') ||
            spotCheck(row, col - 1, 'K') ||
            spotCheck(row - 1, col - 1, 'K') ||
            spotCheck(row - 1, col, 'K') ||
            spotCheck(row - 1, col + 1, 'K') ||
            spotCheck(row, col + 1, 'K'))
        {
            return true;
        }
    }
    return false;
}

void Board::rMoves(vector<int> &moves, int loc)
{
    lineMoves(moves, loc, loc, 1, 0);
    lineMoves(moves, loc, loc, -1, 0);
    lineMoves(moves, loc, loc, 0, 1);
    lineMoves(moves, loc, loc, 0, -1);
}

void Board::bMoves(vector<int> &moves, int loc)
{
    lineMoves(moves, loc, loc, 1, 1);
    lineMoves(moves, loc, loc, 1, -1);
    lineMoves(moves, loc, loc, -1, 1);
    lineMoves(moves, loc, loc, -1, -1);
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
    addMove(moves, loc, row + 2, col + 1);
    addMove(moves, loc, row - 2, col + 1);
    addMove(moves, loc, row + 2, col - 1);
    addMove(moves, loc, row - 2, col - 1);
    addMove(moves, loc, row + 1, col + 2);
    addMove(moves, loc, row - 1, col + 2);
    addMove(moves, loc, row + 1, col - 2);
    addMove(moves, loc, row - 1, col - 2);
}

void Board::pMoves(vector<int> &moves, int loc)
{
    int row = loc / 8;
    int col = loc % 8;
    if (isWhite)
    {
        if (board[loc + 8] == '0')
        {
            addMove(moves, loc, row + 1, col);
        }
        if (row == 1 && moves.size() > 0 && board[loc + 16] == '0')
        {
            addMove(moves, loc, row + 2, col);
            w_ep = loc + 16;
        }
        if (row + 1 < 8 && row + 1 > -1 && col + 1 < 8 && col + 1 > -1 && board[loc + 9] != '0' && !isupper(board[loc + 9]))
        {
            addMove(moves, loc, row + 1, col + 1);
        }
        if (row + 1 < 8 && row + 1 > -1 && col - 1 < 8 && col - 1 > -1 && board[loc + 7] != '0' && !isupper(board[loc + 7]))
        {
            addMove(moves, loc, row + 1, col - 1);
        }
        if (b_ep == loc + 1 && row < 8 && row > -1 && col + 1 < 8 && col + 1 > -1 && !isupper(board[loc + 1]))
        {
            addMove(moves, loc, row, col + 1);
        }
        if (b_ep == loc - 1 && row < 8 && row > -1 && col - 1 < 8 && col - 1 > -1 && !isupper(board[loc - 1]))
        {
            addMove(moves, loc, row, col - 1);
        }
    }
    else
    {
        if (board[loc - 8] == '0')
        {
            addMove(moves, loc, row - 1, col);
        }
        if (row == 6 && moves.size() > 0 && board[loc - 16] == '0')
        {
            addMove(moves, loc, row - 2, col);
            b_ep = loc - 16;
        }
        if (row - 1 < 8 && row - 1 > -1 && col - 1 < 8 && col - 1 > -1 && board[loc - 9] != '0' && isupper(board[loc - 9]))
        {
            addMove(moves, loc, row - 1, col - 1);
        }
        if (row - 1 < 8 && row - 1 > -1 && col + 1 < 8 && col + 1 > -1 && board[loc - 7] != '0' && isupper(board[loc - 7]))
        {
            addMove(moves, loc, row - 1, col + 1);
        }
        if (w_ep == loc + 1 && row < 8 && row > -1 && col + 1 < 8 && col + 1 > -1 && isupper(board[loc + 1]))
        {
            addMove(moves, loc, row, col + 1);
        }
        if (w_ep == loc - 1 && row < 8 && row > -1 && col - 1 < 8 && col - 1 > -1 && isupper(board[loc - 1]))
        {
            addMove(moves, loc, row, col - 1);
        }
    }
}

void Board::kMoves(vector<int> &moves, int loc)
{
    int row = loc / 8;
    int col = loc % 8;

    if (isWhite)
    {
        w_king += 9;
        addMove(moves, loc, row + 1, col + 1);
        w_king += -1;
        addMove(moves, loc, row + 1, col);
        w_king += -1;
        addMove(moves, loc, row + 1, col - 1);
        w_king += -8;
        addMove(moves, loc, row, col - 1);
        w_king += -8;
        addMove(moves, loc, row - 1, col - 1);
        w_king += 1;
        addMove(moves, loc, row - 1, col);
        w_king += 1;
        addMove(moves, loc, row - 1, col + 1);
        w_king += 8;
        addMove(moves, loc, row, col + 1);
        w_king = loc;
    }
    else
    {
        b_king += 9;
        addMove(moves, loc, row + 1, col + 1);
        b_king += -1;
        addMove(moves, loc, row + 1, col);
        b_king += -1;
        addMove(moves, loc, row + 1, col - 1);
        b_king += -8;
        addMove(moves, loc, row, col - 1);
        b_king += -8;
        addMove(moves, loc, row - 1, col - 1);
        b_king += 1;
        addMove(moves, loc, row - 1, col);
        b_king += 1;
        addMove(moves, loc, row - 1, col + 1);
        b_king += 8;
        addMove(moves, loc, row, col + 1);
        b_king = loc;
    }
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