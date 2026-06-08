#include "Game.hpp"

Game::Game(GameMode mode, Difficulty diff) : mode(mode), difficulty(diff) {}    // TODO: manca la window

void Game::run()
{
    while (true)        // TODO: manca la window, while (window.isOpen())
    {
        // 1. Input
        processInput();

        // 2. Update
        update();

        // 3. Renderer
        render();
    }
}

void Game::processInput()
{

}

void Game::update()
{

}

void Game::render()
{

}

void Game::reset()
{
    stato_gioco = GameStatus::InProgress;
    turno_corrente = CellStatus::Player1;
    table = Grid();
}