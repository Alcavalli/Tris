#include "Renderer.hpp"
#include <string>
#include <stdexcept>

Renderer::Renderer()
{
    if (!font.openFromFile("assets/font.ttf"))
        throw std::runtime_error("ERROR: font not found in assets/font.ttf");

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