#pragma once

#include "Constants.hpp"
#include "Enums.hpp"
#include <array>

class Grid
{
private:
    std::array<std::array<CellStatus, Constants::COLS>, Constants::ROWS> griglia{};
    //* {} inizializza tutto a zero (primo elemento, Empty) così da evitare valori spazzatura

public:
    Grid();
    const CellStatus& getCell(int row, int col) const;              //! bastano 2 const
    void setCell(int row, int col, CellStatus nuovo_stato);         //! per i tipi semplici si può passare anche solo per valore (senza const&)
    CellStatus checkWinner() const;     //* controlla se c'è un tris, se non c'è restituisce Empty
    bool isFull() const;                //* controlla se è piena (pareggio)
};