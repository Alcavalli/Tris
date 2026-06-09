#include "AI.hpp"

AI::AI(Difficulty diff) : difficulty(diff) {}

int AI::minimax(Grid table, bool is_maximizing)
{
    if (table.checkWinner() == CellStatus::Player1)     return 1;
    if (table.checkWinner() == CellStatus::Player2)     return -1;
    if (table.isFull())     return 0;

    if (is_maximizing)          //* Tocca all'AI
    {
        for (int i{}; i < Constants::ROWS; ++i)
            for (int j{}; j < Constants::COLS; ++j)
                if (table.getCell(i, j) == CellStatus::Empty)
                {
                    table.setCell(i, j, CellStatus::Player2);       //* Definiamo l'AI come player 2
                    return minimax(table, !is_maximizing);
                }
    }
    else                        //* Tocca al giocatore
    {
        for (int i{}; i < Constants::ROWS; ++i)
            for (int j{}; j < Constants::COLS; ++j)
                if (table.getCell(i, j) == CellStatus::Empty)
                {
                    table.setCell(i, j, CellStatus::Player1);       //* Definiamo l'utente come player 1
                    return minimax(table, !is_maximizing);
                }
    }
}

std::pair<int, int> AI::randomMove(const Grid& table)
{

}

std::pair<int, int> AI::makeMove(const Grid& table)
{

}