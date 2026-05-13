#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:

   sf::Texture m_texture;

sf::Sprite m_sprite;

    float m_speed;

public:

    Player();

    void handleInput();

    void update();

    void render(sf::RenderWindow& window);
};