#pragma once

#include <SFML/Graphics.hpp>

class Renderer
{
public:
    void renderHud(sf::RenderWindow& window,
                   float healthRatio,
                   bool showTravelTimer,
                   float travelRatio);

private:
    void drawBar(sf::RenderWindow& window,
                 sf::Vector2f position,
                 sf::Vector2f size,
                 float ratio,
                 sf::Color fillColor,
                 sf::Color backColor,
                 sf::Color outlineColor);
};
