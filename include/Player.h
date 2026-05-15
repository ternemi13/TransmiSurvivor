#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Texture m_frontTexture;
    sf::Texture m_backTexture;
    sf::Texture m_leftTexture;
    sf::Texture m_rightTexture;
    sf::Sprite m_sprite;
    float m_speed;

public:
    Player();

    void setPosition(sf::Vector2f position);
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
};
