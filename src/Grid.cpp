#include "Grid.hpp"

const CellStatus& Grid::getCell(int row, int col) const
{
    return table[row][col];
}

void Grid::setCell(int row, int col, CellStatus nuovo_stato)
{
    if (table[row][col] == CellStatus::Empty)
        table[row][col] = nuovo_stato;
}

CellStatus Grid::checkWinner() const
{
    for (int i{}; i < Constants::ROWS; ++i)
        if (table[i][0] != CellStatus::Empty && table[i][0] == table[i][1] && table[i][0] == table[i][2])
            return table[i][0];

    for (int j{}; j < Constants::COLS; ++j)
        if (table[0][j] != CellStatus::Empty && table[0][j] == table[1][j] && table[0][j] == table[2][j])
            return table[0][j];

    if (table[1][1] != CellStatus::Empty && ((table[1][1] == table[0][0] && table[1][1] == table[2][2]) || (table[1][1] == table[0][2] && table[1][1] == table[2][0])))
        return table[1][1];

    return CellStatus::Empty;
}

bool Grid::isFull() const
{
    for (int i{}; i < Constants::ROWS; ++i)
        for (int j{}; j < Constants::COLS; ++j)
            if (table[i][j] == CellStatus::Empty)   return false;
    return true;
}