#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:

   sf::Texture m_texture;
   sf::Texture m_frontTexture;

sf::Texture m_backTexture;

sf::Texture m_leftTexture;

sf::Texture m_rightTexture;

sf::Sprite m_sprite;



    float m_speed;

public:

    Player();

    void handleInput();

    void update(float deltaTime);

    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
};