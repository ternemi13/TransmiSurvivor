#include "Enemy.h"

#include <cmath>

Enemy::Enemy()
    : m_speed(85.0f),
      m_active(false)
{
}

bool Enemy::spawn(const char* spritePath, sf::Vector2f position)
{
    if (!m_texture.loadFromFile(spritePath))
    {
        m_active = false;
        return false;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(position);
    m_sprite.setScale(0.12f, 0.12f);
    m_active = true;

    return true;
}

void Enemy::update(float deltaTime, sf::Vector2f targetPosition)
{
    if (!m_active)
    {
        return;
    }

    const sf::FloatRect enemyBounds = m_sprite.getGlobalBounds();
    const sf::Vector2f enemyCenter(
        enemyBounds.left + enemyBounds.width * 0.5f,
        enemyBounds.top + enemyBounds.height * 0.5f
    );

    sf::Vector2f direction(
        targetPosition.x - enemyCenter.x,
        targetPosition.y - enemyCenter.y
    );

    const float distance = std::sqrt(
        direction.x * direction.x +
        direction.y * direction.y
    );

    if (distance < 1.0f)
    {
        return;
    }

    direction.x /= distance;
    direction.y /= distance;

    m_sprite.move(
        direction.x * m_speed * deltaTime,
        direction.y * m_speed * deltaTime
    );
}

void Enemy::render(sf::RenderWindow& window)
{
    if (m_active)
    {
        window.draw(m_sprite);
    }
}

bool Enemy::isActive() const
{
    return m_active;
}
