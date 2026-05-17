#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
    enum class FacingDirection
    {
        Front,
        Back,
        Left,
        Right
    };

    sf::Texture m_frontTexture;
    sf::Texture m_backTexture;
    sf::Texture m_leftTexture;
    sf::Texture m_rightTexture;
    sf::Sprite m_sprite;
    FacingDirection m_facingDirection;
    float m_speed;
    int m_health;
    bool m_active;

    void setFacingDirection(FacingDirection facingDirection);

public:
    Enemy();

    bool spawn(const char* frontSpritePath,
               const char* backSpritePath,
               const char* leftSpritePath,
               const char* rightSpritePath,
               sf::Vector2f position);
    void update(float deltaTime, sf::Vector2f targetPosition);
    void takeDamage(int damage);
    void render(sf::RenderWindow& window);
    bool isActive() const;
    sf::FloatRect getBounds() const;
};
