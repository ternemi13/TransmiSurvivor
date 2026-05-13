#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:

    sf::RectangleShape m_shape;

    float m_speed;

public:

    Player();

    void handleInput();

    void update();

    void render(sf::RenderWindow& window);
};