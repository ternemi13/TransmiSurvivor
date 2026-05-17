#include "Enemy.h"

Enemy::Enemy()
    : m_active(false)
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
