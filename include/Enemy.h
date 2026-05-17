#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float m_speed;
    int m_health;
    bool m_active;

public:
    Enemy();

    bool spawn(const char* spritePath, sf::Vector2f position);
    void update(float deltaTime, sf::Vector2f targetPosition);
    void takeDamage(int damage);
    void render(sf::RenderWindow& window);
    bool isActive() const;
    sf::FloatRect getBounds() const;
};
