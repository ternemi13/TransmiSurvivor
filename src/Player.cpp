#include "Player.h"

Player::Player()
{
    m_texture.loadFromFile("../assets/sprites/player/player.png");

m_sprite.setTexture(m_texture);

m_sprite.setPosition(200.0f, 200.0f);

m_sprite.setScale(0.2f, 0.2f);

m_speed = 0.08f;

    m_speed = 0.1f;
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_sprite.move(0.0f, -m_speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_sprite.move(0.0f, m_speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
       m_sprite.move(-m_speed, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
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