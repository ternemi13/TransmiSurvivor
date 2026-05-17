#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    bool m_active;

public:
    Enemy();

    bool spawn(const char* spritePath, sf::Vector2f position);
    void render(sf::RenderWindow& window);
    bool isActive() const;
};
