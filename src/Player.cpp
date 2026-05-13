#include "Player.h"

Player::Player()
{
    m_frontTexture.loadFromFile("../assets/sprites/player/player.png");

m_backTexture.loadFromFile("../assets/sprites/player/back.png");

m_leftTexture.loadFromFile("../assets/sprites/player/left.png");

m_rightTexture.loadFromFile("../assets/sprites/player/right.png");

m_sprite.setTexture(m_frontTexture);
m_sprite.setPosition(200.0f, 200.0f);

m_sprite.setScale(0.2f, 0.2f);

m_speed = 0.08f;

    m_speed = 0.1f;
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_sprite.setTexture(m_backTexture);
        m_sprite.move(0.0f, -m_speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_sprite.setTexture(m_frontTexture);
        m_sprite.move(0.0f, m_speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_sprite.setTexture(m_leftTexture);
       m_sprite.move(-m_speed, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_sprite.setTexture(m_rightTexture);
        m_sprite.move(m_speed, 0.0f);
    }
}

void Player::update()
{
    handleInput();
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}