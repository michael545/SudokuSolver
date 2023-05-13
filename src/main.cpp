#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 9;

bool isValid(vector<vector<int>> &board, int row, int col, int num)
{
    // Check if 'num' is already present in the same row or column
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check if 'num' is already present in the same 3x3 sub-grid
    int subgridRow = row - row % 3;
    int subgridCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[subgridRow + i][subgridCol + j] == num)
                return false;
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>> &board)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (board[row][col] == 0)
            { // Empty cell
                for (int num = 1; num <= 9; ++num)
                {
                    if (isValid(board, row, col, num))
                    {
                        board[row][col] = num; // Place the number

                        if (solveSudoku(board)) // Recursive call
                            return true;

                        board[row][col] = 0; // Backtrack and try a different number
                    }
                }
                return false; // No valid number found for this cell
            }
        }
    }
    return true; // Puzzle solved
}

void printBoard(const vector<vector<int>> *board)
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            cout << (*(board))[row][col] << " ";
            // cout << board->at(row).at(col) << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> board = {
        {0, 0, 0, 0, 9, 4, 0, 3, 0},
        {0, 0, 0, 5, 1, 0, 0, 0, 7},
        {0, 8, 9, 0, 0, 0, 0, 4, 0},
        {0, 0, 0, 0, 0, 0, 2, 0, 8},
        {0, 6, 0, 2, 0, 1, 0, 5, 0},
        {1, 0, 2, 0, 0, 0, 0, 0, 0},
        {0, 9, 0, 0, 0, 0, 5, 2, 0},
        {2, 0, 0, 0, 4, 8, 0, 0, 0},
        {0, 7, 0, 6, 5, 0, 0, 0, 0}};

    cout << "\n Sudoku Puzzle: \n"
         << endl;
    printBoard(&board);
    cout << "\n"
         << endl;
    solveSudoku(board);
    cout << "Solved puzzle is: \n"
         << endl;

    printBoard(&board);

    return 0;
}