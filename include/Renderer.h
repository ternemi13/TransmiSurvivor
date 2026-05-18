#pragma once

#include <SFML/Graphics.hpp>

class Renderer
{
public:
    void renderHud(sf::RenderWindow& window,
                   float healthRatio,
                   bool showTravelTimer,
                   float travelRatio,
                   bool showPlatformTimer,
                   float platformRatio,
                   int aliveEnemyCount,
                   int maxEnemyCount);

private:
    void drawBar(sf::RenderWindow& window,
                 sf::Vector2f position,
                 sf::Vector2f size,
                 float ratio,
                 sf::Color fillColor,
                 sf::Color backColor,
                 sf::Color outlineColor);
    void drawEnemyCounter(sf::RenderWindow& window,
                          sf::Vector2f position,
                          int aliveEnemyCount,
                          int maxEnemyCount);
    void drawNumber(sf::RenderWindow& window,
                    sf::Vector2f position,
                    int number,
                    float scale,
                    sf::Color color);
    void drawDigit(sf::RenderWindow& window,
                   sf::Vector2f position,
                   int digit,
                   float scale,
                   sf::Color color);
    void drawSegment(sf::RenderWindow& window,
                     sf::Vector2f position,
                     sf::Vector2f size,
                     sf::Color color);
};
