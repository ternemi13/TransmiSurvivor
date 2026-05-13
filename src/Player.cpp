#include "Player.h"

Player::Player()
{
    m_shape.setSize(sf::Vector2f(50.0f, 50.0f));

    m_shape.setFillColor(sf::Color::Green);

    m_shape.setPosition(200.0f, 200.0f);

    m_speed = 0.3f;
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_shape.move(0.0f, -m_speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_shape.move(0.0f, m_speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_shape.move(-m_speed, 0.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_shape.move(m_speed, 0.0f);
    }
}

void Player::update()
{
    handleInput();
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_shape);
}