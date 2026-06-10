#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <optional>         //? Per i testi per SFML 3

class Renderer
{
private:
    sf::Font font;
    std::optional<sf::Text> text_gameOver, text_turno, text_punteggio, text_restart;
    sf::RectangleShape background, v_line1, v_line2, h_line1, h_line2;
    sf::Clock blink;
    bool textStatus{};
    sf::Vector2f toPixel(const sf::Vector2i& cell) const;

public:
    Renderer();
    void render(sf::RenderWindow& window, const Grid& table, GameStatus stato_gioco, CellStatus turno_corrente);
};