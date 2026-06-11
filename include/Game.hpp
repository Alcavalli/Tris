#pragma once

#include "Grid.hpp"             //* Constants.hpp e Enums.hpp già inclusi con Grid.hpp
#include "Renderer.hpp"
#include "AI.hpp"

class Game
{
private:
    GameStatus stato_gioco{GameStatus::Menu};
    CellStatus turno_corrente{CellStatus::Player1};
    GameMode mode;           //! default in caso di fallback, va nel constructor
    AI environment;
    Grid table;
    sf::RenderWindow window;
    sf::Clock ai_clock;
    bool ai_waiting{};
    Renderer renderer;

public:
    Game(GameMode mode = GameMode::PvE, Difficulty diff = Difficulty::Easy);
    void run();
    void processInput();
    void update(int row, int col);
    void render();
    void reset();
};