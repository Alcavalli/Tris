#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.hpp"             //! Constants e Enums sono già inclusi, sarebbero ridondanti

class Renderer
{
private:
    sf::Font font;
    sf::Text testo_game_over, testo_turno, testo_punteggio, testo_restart;
    sf::Clock lampeggio;
    bool visibile{};
    sf::Vector2f toPixel(const sf::Vector2i& cella) const;

public:
    Renderer();
    void render(sf::RenderWindow& window, const Grid& table, const GameStatus& stato_gioco, const CellStatus& turno_corrente);
};