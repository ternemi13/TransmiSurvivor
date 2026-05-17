#include "Enemy.h"

#include <cmath>

Enemy::Enemy()
    : m_facingDirection(FacingDirection::Front),
      m_speed(85.0f),
      m_health(0),
      m_active(false)
{
}

bool Enemy::spawn(const char* frontSpritePath,
                  const char* backSpritePath,
                  const char* leftSpritePath,
                  const char* rightSpritePath,
                  sf::Vector2f position)
{
    const bool loaded =
        m_frontTexture.loadFromFile(frontSpritePath) &&
        m_backTexture.loadFromFile(backSpritePath) &&
        m_leftTexture.loadFromFile(leftSpritePath) &&
        m_rightTexture.loadFromFile(rightSpritePath);

    if (!loaded)
    {
        m_active = false;
        return false;
    }

    m_sprite.setTexture(m_frontTexture, true);
    m_sprite.setPosition(position);
    m_sprite.setScale(0.12f, 0.12f);
    m_facingDirection = FacingDirection::Front;
    m_health = 3;
    m_active = true;

    return true;
}

void Enemy::setFacingDirection(FacingDirection facingDirection)
{
    if (m_facingDirection == facingDirection)
    {
        return;
    }

    const sf::FloatRect previousBounds = m_sprite.getGlobalBounds();
    const sf::Vector2f previousFeet(
        previousBounds.left + previousBounds.width * 0.5f,
        previousBounds.top + previousBounds.height
    );

    switch (facingDirection)
    {
    case FacingDirection::Front:
        m_sprite.setTexture(m_frontTexture, true);
        break;
    case FacingDirection::Back:
        m_sprite.setTexture(m_backTexture, true);
        break;
    case FacingDirection::Left:
        m_sprite.setTexture(m_leftTexture, true);
        break;
    case FacingDirection::Right:
        m_sprite.setTexture(m_rightTexture, true);
        break;
    }

    const sf::FloatRect newBounds = m_sprite.getGlobalBounds();
    m_sprite.setPosition(
        previousFeet.x - newBounds.width * 0.5f,
        previousFeet.y - newBounds.height
    );
    m_facingDirection = facingDirection;
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

    if (std::abs(direction.x) > std::abs(direction.y))
    {
        if (direction.x < 0.0f)
        {
            setFacingDirection(FacingDirection::Left);
        }
        else
        {
            setFacingDirection(FacingDirection::Right);
        }
    }
    else
    {
        if (direction.y < 0.0f)
        {
            setFacingDirection(FacingDirection::Back);
        }
        else
        {
            setFacingDirection(FacingDirection::Front);
        }
    }

    m_sprite.move(
        direction.x * m_speed * deltaTime,
        direction.y * m_speed * deltaTime
    );
}

void Enemy::takeDamage(int damage)
{
    if (!m_active)
    {
        return;
    }

    m_health -= damage;

    if (m_health <= 0)
    {
        m_health = 0;
        m_active = false;
    }
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

sf::FloatRect Enemy::getBounds() const
{
    return m_sprite.getGlobalBounds();
}
