#include "Renderer.hpp"
#include <string>
#include <stdexcept>

Renderer::Renderer()
{
    //* Caricamento del font
    if (!font.openFromFile("assets/font.ttf"))
        throw std::runtime_error("ERROR: font not found in assets/font.ttf");

    //* Creazione dello sfondo
    background.setSize({static_cast<float>(Constants::WINDOW_WIDTH), static_cast<float>(Constants::WINDOW_HEIGHT)});
    background.setFillColor(sf::Color(206, 206, 126));
    background.setPosition({0, 0});

    //* Creazione della griglia
    v_line1.setSize({static_cast<float>(Constants::LINES_WIDTH), static_cast<float>(Constants::LINES_LENGHT)});
    v_line2.setSize({static_cast<float>(Constants::LINES_WIDTH), static_cast<float>(Constants::LINES_LENGHT)});
    h_line1.setSize({static_cast<float>(Constants::LINES_LENGHT), static_cast<float>(Constants::LINES_WIDTH)});
    h_line2.setSize({static_cast<float>(Constants::LINES_LENGHT), static_cast<float>(Constants::LINES_WIDTH)});
    v_line1.setFillColor(sf::Color(3, 3, 48));
    v_line2.setFillColor(sf::Color(3, 3, 48));
    h_line1.setFillColor(sf::Color(3, 3, 48));
    h_line2.setFillColor(sf::Color(3, 3, 48));
    v_line1.setPosition({static_cast<float>(Constants::CELL_SIZE), 0});
    v_line2.setPosition({static_cast<float>(Constants::CELL_SIZE) * 2 + Constants::LINES_WIDTH, 0});
    h_line1.setPosition({0, static_cast<float>(Constants::CELL_SIZE)});
    h_line2.setPosition({0, static_cast<float>(Constants::CELL_SIZE) * 2 + Constants::LINES_WIDTH});

    //* Creazione dei testi (invarianti)
    text_gameOver.emplace(font);        //* Si usa .emplace
    text_gameOver->setString("Game Over");          //! Occhio alle frecce e non punti
    text_gameOver->setCharacterSize(80);
    text_gameOver->setFillColor(sf::Color::Red);
    sf::FloatRect bounds_gameOver{text_gameOver->getLocalBounds()};
    text_gameOver->setOrigin({(bounds_gameOver.position.x + bounds_gameOver.size.x) / 2.f, (bounds_gameOver.position.y + bounds_gameOver.size.y) / 2.f});    //! I bounds hanno ora come metodi .position.x/y e .size.x/y, e setOrigin accetta un sf::Vector2f
    text_gameOver->setPosition({Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT / 2.f});
    //! Occhio alle graffe, in SFML 3 accetta un sf::Vector2f, non 2 float (come per setOrigin)
}

sf::Vector2f Renderer::toPixel(const sf::Vector2i &cell) const
{
    return sf::Vector2f(static_cast<float>(cell.x) * Constants::CELL_SIZE, static_cast<float>(cell.y) * Constants::CELL_SIZE);
}

void Renderer::render(sf::RenderWindow &window, const Grid &table, GameStatus stato_gioco, CellStatus turno_corrente)
{
    // 1. Pulire la finestra
    window.clear();

    // 2. Disegnare gli elementi

    // 3. Mostrare il frame
    window.display();
}