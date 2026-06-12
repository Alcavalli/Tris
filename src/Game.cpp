#include "Game.hpp"

Game::Game(GameMode mode, Difficulty diff) : mode(mode), environment(diff), window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}), "Tic-Tac-Toe") {}

void Game::run()
{
    while (window.isOpen())
    {
        // 1. Input + Update integrato
        processInput();

        // 2. Delay turno AI
        if (ai_waiting && ai_clock.getElapsedTime().asMilliseconds() >= 500)
        {
            ai_waiting = false;
            if (stato_gioco == GameStatus::InProgress && !restart_waiting)
            {
                auto [row_ai, col_ai] = environment.makeMove(table);
                table.setCell(row_ai, col_ai, CellStatus::Player2);
                switch (table.checkWinner())
                {
                case CellStatus::Empty:
                    if (table.isFull())
                    {
                        prossimo_stato = GameStatus::Draw;
                        restart_waiting = true;
                        restart_clock.restart();
                    }
                    else
                        turno_corrente = CellStatus::Player1;
                    break;
                case CellStatus::Player1:
                    prossimo_stato = GameStatus::Player1Win;
                    restart_waiting = true;
                    restart_clock.restart();
                    break;
                case CellStatus::Player2:
                    prossimo_stato = GameStatus::Player2Win;
                    restart_waiting = true;
                    restart_clock.restart();
                    break;
                }
            }
        }

        // 3. Delay game over
        if (restart_waiting && restart_clock.getElapsedTime().asMilliseconds() >= 750)
        {
            restart_waiting = false;
            stato_gioco = prossimo_stato;
        }

        // 4. Renderer
        render();
    }
}

void Game::handleClick(sf::Vector2i pos)
{
    switch (stato_gioco)
    {
    case GameStatus::Menu:
        if (renderer.getButton(ButtonTypes::PvP)->isClicked(pos))
        {
            reset();
            mode = GameMode::PvP;
            stato_gioco = GameStatus::InProgress;
        }
        else if (renderer.getButton(ButtonTypes::Easy)->isClicked(pos))
        {
            mode = GameMode::PvE;
            environment = AI(Difficulty::Easy);
            stato_gioco = GameStatus::OrderSelection;
        }
        else if (renderer.getButton(ButtonTypes::Mid)->isClicked(pos))
        {
            mode = GameMode::PvE;
            environment = AI(Difficulty::Medium);
            stato_gioco = GameStatus::OrderSelection;
        }
        else if (renderer.getButton(ButtonTypes::Hard)->isClicked(pos))
        {
            mode = GameMode::PvE;
            environment = AI(Difficulty::Hard);
            stato_gioco = GameStatus::OrderSelection;
        }
        break;
    case GameStatus::OrderSelection:
        if (renderer.getButton(ButtonTypes::First)->isClicked(pos))
        {
            reset();
            stato_gioco = GameStatus::InProgress;
        }
        else if (renderer.getButton(ButtonTypes::Second)->isClicked(pos))
        {
            reset();
            stato_gioco = GameStatus::InProgress;
            ai_waiting = true;
            ai_clock.restart();
        }
        else if (renderer.getButton(ButtonTypes::Back)->isClicked(pos))
        {
            mode = GameMode::PvE;
            environment = AI(Difficulty::Easy);
            stato_gioco = GameStatus::Menu;
        }
        break;
    case GameStatus::InProgress:
        if (renderer.getButton(ButtonTypes::Back)->isClicked(pos))
            stato_gioco = GameStatus::Menu;
        else
            update((pos.y - Constants::GRID_OFFSET_Y) / Constants::CELL_SIZE, (pos.x - Constants::GRID_OFFSET_X) / Constants::CELL_SIZE); //! Ricorda: riga e colonna, quindi y e x (non x e y)
        break;
    default:
        break;
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
                handleClick(mouseClick->position);

        if (const auto* touch{event->getIf<sf::Event::TouchBegan>()})
                handleClick(sf::Vector2i(touch->position));

        if (const auto *keyPress{event->getIf<sf::Event::KeyPressed>()})
            if (stato_gioco != GameStatus::InProgress && stato_gioco != GameStatus::Menu && stato_gioco != GameStatus::OrderSelection && !restart_waiting)
                reset();
    }
}

void Game::update(int row, int col)
{
    if (row < 0 || row >= Constants::ROWS || col < 0 || col >= Constants::COLS)
        return;
    if (stato_gioco != GameStatus::InProgress)
        return;
    if (table.getCell(row, col) != CellStatus::Empty)
        return;

    table.setCell(row, col, turno_corrente);
    switch (table.checkWinner())
    {
    case CellStatus::Empty:
        if (table.isFull())
        {
            prossimo_stato = GameStatus::Draw;
            restart_waiting = true;
            restart_clock.restart();
        }
        else
            turno_corrente = (turno_corrente == CellStatus::Player1) ? CellStatus::Player2 : CellStatus::Player1;
        break;
    case CellStatus::Player1:
        prossimo_stato = GameStatus::Player1Win;
        restart_waiting = true;
        restart_clock.restart();
        break;
    case CellStatus::Player2:
        prossimo_stato = GameStatus::Player2Win;
        restart_waiting = true;
        restart_clock.restart();
        break;
    }

    if (mode == GameMode::PvE && stato_gioco == GameStatus::InProgress)
    {
        ai_waiting = true;
        ai_clock.restart();
    }
}

void Game::render()
{
    renderer.render(window, table, stato_gioco, turno_corrente);
}

void Game::reset()
{
    stato_gioco = GameStatus::InProgress;
    turno_corrente = CellStatus::Player1;
    table = Grid();
}