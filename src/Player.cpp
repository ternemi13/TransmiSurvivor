#include "Player.h"

#include <cmath>

Player::Player()
{
    m_frontTexture.loadFromFile("../assets/sprites/player/player.png");
    m_backTexture.loadFromFile("../assets/sprites/player/back.png");
    m_leftTexture.loadFromFile("../assets/sprites/player/left.png");
    m_rightTexture.loadFromFile("../assets/sprites/player/right.png");

    m_sprite.setTexture(m_frontTexture);
    m_sprite.setPosition(200.0f, 200.0f);
    m_sprite.setScale(0.2f, 0.2f);
    m_speed = 250.0f;
}

void Player::handleInput(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_sprite.setTexture(m_backTexture);
        movement.y -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_sprite.setTexture(m_frontTexture);
        movement.y += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_sprite.setTexture(m_leftTexture);
        movement.x -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_sprite.setTexture(m_rightTexture);
        movement.x += 1.0f;
    }

    if (movement.x != 0.0f || movement.y != 0.0f)
    {
        const float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;

        m_sprite.move(movement.x * m_speed * deltaTime,
                      movement.y * m_speed * deltaTime);
    }
}

void Player::update(float deltaTime)
{
    handleInput(deltaTime);
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

sf::FloatRect Player::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Player::setPosition(sf::Vector2f position)
{
    m_sprite.setPosition(position);
}
