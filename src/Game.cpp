#include "Game.hpp"

Game::Game(GameMode mode, Difficulty diff) : mode(mode), difficulty(diff), window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Tic-Tac-Toe") {}

void Game::run()
{
    while (window.isOpen())
    {
        // 1. Input + Update integrato
        processInput();

        // 2. Renderer
        render();
    }
}

void Game::processInput()
{
    while (const std::optional<sf::Event> event{window.pollEvent()})
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto *mouseClick{event->getIf<sf::Event::MouseButtonPressed>()})
            if (mouseClick->button == sf::Mouse::Button::Left)
                update(mouseClick->position.y / Constants::CELL_SIZE, mouseClick->position.x / Constants::CELL_SIZE);       //! Ricorda: riga e colonna, quindi y e x (non x e y)
    }
}

void Game::update(int row, int col)
{
    if (table.getCell(row, col) != CellStatus::Empty)
        throw std::runtime_error("ERROR: the cell is already occupied");
    else
    {
        table.setCell(row, col, turno_corrente);
        switch(table.checkWinner())
        {
            case CellStatus::Empty:
                if (table.isFull())
                    stato_gioco = GameStatus::Draw;
                else
                    turno_corrente = (turno_corrente == CellStatus::Player1) ? CellStatus::Player2 : CellStatus::Player1;
                break;
            case CellStatus::Player1:
                stato_gioco = GameStatus::Player1Win;
                break;
            case CellStatus::Player2:
                stato_gioco = GameStatus::Player2Win;
                break;
        }
    }
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