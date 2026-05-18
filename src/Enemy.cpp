#include "Enemy.h"

#include <cmath>

namespace
{
sf::IntRect getVisibleRect(const sf::Image& image)
{
    const sf::Vector2u size = image.getSize();
    unsigned int minX = size.x;
    unsigned int minY = size.y;
    unsigned int maxX = 0;
    unsigned int maxY = 0;
    bool foundPixel = false;

    for (unsigned int y = 0; y < size.y; y++)
    {
        for (unsigned int x = 0; x < size.x; x++)
        {
            if (image.getPixel(x, y).a > 10)
            {
                if (x < minX)
                {
                    minX = x;
                }

                if (y < minY)
                {
                    minY = y;
                }

                if (x > maxX)
                {
                    maxX = x;
                }

                if (y > maxY)
                {
                    maxY = y;
                }

                foundPixel = true;
            }
        }
    }

    if (!foundPixel)
    {
        return sf::IntRect(0, 0, size.x, size.y);
    }

    return sf::IntRect(
        static_cast<int>(minX),
        static_cast<int>(minY),
        static_cast<int>(maxX - minX + 1),
        static_cast<int>(maxY - minY + 1)
    );
}

bool loadTextureWithVisibleRect(const char* path,
                                sf::Texture& texture,
                                sf::IntRect& visibleRect)
{
    sf::Image image;

    if (!image.loadFromFile(path))
    {
        return false;
    }

    visibleRect = getVisibleRect(image);
    return texture.loadFromImage(image);
}
}

Enemy::Enemy()
    : m_facingDirection(FacingDirection::Front),
      m_normalScale(0.12f),
      m_attackScale(0.18f),
      m_speed(85.0f),
      m_attackRange(58.0f),
      m_attackFrameTime(0.12f),
      m_attackTimer(0.0f),
      m_attackCooldown(0.55f),
      m_attackCooldownTimer(0.0f),
      m_feedbackTimer(0.0f),
      m_attackFrame(0),
      m_attackId(0),
      m_health(0),
      m_active(false),
      m_isAttacking(false)
{
}

bool Enemy::spawn(const char* frontSpritePath,
                  const char* backSpritePath,
                  const char* leftSpritePath,
                  const char* rightSpritePath,
                  const char* attackLeftFrame0Path,
                  const char* attackLeftFrame1Path,
                  const char* attackLeftFrame2Path,
                  const char* attackRightFrame0Path,
                  const char* attackRightFrame1Path,
                  const char* attackRightFrame2Path,
                  sf::Vector2f position)
{
    const bool loaded =
        m_frontTexture.loadFromFile(frontSpritePath) &&
        m_backTexture.loadFromFile(backSpritePath) &&
        m_leftTexture.loadFromFile(leftSpritePath) &&
        m_rightTexture.loadFromFile(rightSpritePath) &&
        loadTextureWithVisibleRect(
            attackLeftFrame0Path,
            m_attackLeftTextures[0],
            m_attackLeftRects[0]
        ) &&
        loadTextureWithVisibleRect(
            attackLeftFrame1Path,
            m_attackLeftTextures[1],
            m_attackLeftRects[1]
        ) &&
        loadTextureWithVisibleRect(
            attackLeftFrame2Path,
            m_attackLeftTextures[2],
            m_attackLeftRects[2]
        ) &&
        loadTextureWithVisibleRect(
            attackRightFrame0Path,
            m_attackRightTextures[0],
            m_attackRightRects[0]
        ) &&
        loadTextureWithVisibleRect(
            attackRightFrame1Path,
            m_attackRightTextures[1],
            m_attackRightRects[1]
        ) &&
        loadTextureWithVisibleRect(
            attackRightFrame2Path,
            m_attackRightTextures[2],
            m_attackRightRects[2]
        );

    if (!loaded)
    {
        m_active = false;
        return false;
    }

    m_sprite.setTexture(m_frontTexture, true);
    m_sprite.setPosition(position);
    m_sprite.setScale(m_normalScale, m_normalScale);
    m_facingDirection = FacingDirection::Front;
    m_attackTimer = 0.0f;
    m_attackCooldownTimer = 0.0f;
    m_feedbackTimer = 0.0f;
    m_attackFrame = 0;
    m_isAttacking = false;
    m_health = 3;
    m_active = true;
    m_sprite.setColor(sf::Color::White);

    return true;
}

void Enemy::setFacingDirection(FacingDirection facingDirection)
{
    if (m_facingDirection == facingDirection)
    {
        return;
    }

    switch (facingDirection)
    {
    case FacingDirection::Front:
        setSpriteTexture(m_frontTexture, m_normalScale);
        break;
    case FacingDirection::Back:
        setSpriteTexture(m_backTexture, m_normalScale);
        break;
    case FacingDirection::Left:
        setSpriteTexture(m_leftTexture, m_normalScale);
        break;
    case FacingDirection::Right:
        setSpriteTexture(m_rightTexture, m_normalScale);
        break;
    }

    m_facingDirection = facingDirection;
}

void Enemy::startAttack(FacingDirection attackDirection)
{
    if (m_isAttacking || m_attackCooldownTimer > 0.0f)
    {
        return;
    }

    m_facingDirection = attackDirection;
    m_isAttacking = true;
    m_attackTimer = 0.0f;
    m_attackFrame = 0;
    m_attackId++;
    setAttackFrameTexture();
}

void Enemy::updateAttack(float deltaTime)
{
    if (!m_isAttacking)
    {
        return;
    }

    m_attackTimer += deltaTime;

    if (m_attackTimer < m_attackFrameTime)
    {
        return;
    }

    m_attackTimer = 0.0f;
    m_attackFrame++;

    if (m_attackFrame >= ATTACK_FRAME_COUNT)
    {
        m_isAttacking = false;
        m_attackCooldownTimer = m_attackCooldown;

        if (m_facingDirection == FacingDirection::Left)
        {
            setSpriteTexture(m_leftTexture, m_normalScale);
        }
        else
        {
            setSpriteTexture(m_rightTexture, m_normalScale);
        }

        return;
    }

    setAttackFrameTexture();
}

void Enemy::setAttackFrameTexture()
{
    if (m_facingDirection == FacingDirection::Left)
    {
        setSpriteTexture(
            m_attackLeftTextures[m_attackFrame],
            m_attackScale,
            m_attackLeftRects[m_attackFrame]
        );
    }
    else
    {
        setSpriteTexture(
            m_attackRightTextures[m_attackFrame],
            m_attackScale,
            m_attackRightRects[m_attackFrame]
        );
    }
}

void Enemy::setSpriteTexture(sf::Texture& texture,
                             float scale,
                             sf::IntRect textureRect)
{
    const sf::FloatRect oldBounds = m_sprite.getGlobalBounds();
    const sf::Vector2f oldFeet(
        oldBounds.left + oldBounds.width * 0.5f,
        oldBounds.top + oldBounds.height
    );

    m_sprite.setTexture(texture, true);

    if (textureRect.width > 0 && textureRect.height > 0)
    {
        m_sprite.setTextureRect(textureRect);
    }

    m_sprite.setScale(scale, scale);

    const sf::FloatRect newBounds = m_sprite.getGlobalBounds();
    m_sprite.setPosition(
        oldFeet.x - newBounds.width * 0.5f,
        oldFeet.y - newBounds.height
    );
}

void Enemy::updateFeedback(float deltaTime)
{
    if (m_feedbackTimer <= 0.0f)
    {
        return;
    }

    m_feedbackTimer -= deltaTime;

    if (m_feedbackTimer <= 0.0f)
    {
        m_feedbackTimer = 0.0f;
        m_sprite.setColor(sf::Color::White);
    }
}

void Enemy::applyKnockback(sf::Vector2f sourcePosition, float distance)
{
    const sf::FloatRect bounds = m_sprite.getGlobalBounds();
    const sf::Vector2f center(
        bounds.left + bounds.width * 0.5f,
        bounds.top + bounds.height * 0.5f
    );
    sf::Vector2f direction(
        center.x - sourcePosition.x,
        center.y - sourcePosition.y
    );
    const float length = std::sqrt(
        direction.x * direction.x +
        direction.y * direction.y
    );

    if (length < 0.001f)
    {
        direction.x = m_facingDirection == FacingDirection::Left ? 1.0f : -1.0f;
        direction.y = 0.0f;
    }
    else
    {
        direction.x /= length;
        direction.y /= length;
    }

    m_sprite.move(direction.x * distance, direction.y * distance);
}

void Enemy::update(float deltaTime, sf::Vector2f targetPosition)
{
    if (!m_active)
    {
        return;
    }

    updateFeedback(deltaTime);

    if (m_attackCooldownTimer > 0.0f)
    {
        m_attackCooldownTimer -= deltaTime;

        if (m_attackCooldownTimer < 0.0f)
        {
            m_attackCooldownTimer = 0.0f;
        }
    }

    if (m_isAttacking)
    {
        updateAttack(deltaTime);
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

    if (distance <= m_attackRange)
    {
        if (direction.x < 0.0f)
        {
            setFacingDirection(FacingDirection::Left);
            startAttack(FacingDirection::Left);
        }
        else
        {
            setFacingDirection(FacingDirection::Right);
            startAttack(FacingDirection::Right);
        }

        return;
    }

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

void Enemy::takeDamage(int damage, sf::Vector2f sourcePosition)
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
        m_sprite.setColor(sf::Color::White);
        return;
    }

    m_sprite.setColor(sf::Color(255, 55, 55));
    m_feedbackTimer = 0.08f;
    applyKnockback(sourcePosition, 20.0f);
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

bool Enemy::isAttacking() const
{
    return m_isAttacking;
}

bool Enemy::isAttackDamageActive() const
{
    return m_isAttacking && m_attackFrame > 0;
}

int Enemy::getAttackId() const
{
    return m_attackId;
}

sf::FloatRect Enemy::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

sf::FloatRect Enemy::getAttackBounds() const
{
    if (!isAttackDamageActive())
    {
        return sf::FloatRect();
    }

    return m_sprite.getGlobalBounds();
}
