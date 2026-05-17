#include "Player.h"

#include <cmath>

Player::Player()
{
    m_frontTexture.loadFromFile("../assets/sprites/player/player.png");
    m_backTexture.loadFromFile("../assets/sprites/player/back.png");
    m_leftTexture.loadFromFile("../assets/sprites/player/left.png");
    m_rightTexture.loadFromFile("../assets/sprites/player/right.png");
    m_attackRightTextures[0].loadFromFile("../assets/sprites/player/golpe/golpes derecha/frame_0.png");
    m_attackRightTextures[1].loadFromFile("../assets/sprites/player/golpe/golpes derecha/frame_1.png");
    m_attackRightTextures[2].loadFromFile("../assets/sprites/player/golpe/golpes derecha/frame_2.png");
    m_attackLeftTextures[0].loadFromFile("../assets/sprites/player/golpe/golpe izquierda/frame_0.png");
    m_attackLeftTextures[1].loadFromFile("../assets/sprites/player/golpe/golpe izquierda/frame_1.png");
    m_attackLeftTextures[2].loadFromFile("../assets/sprites/player/golpe/golpe izquierda/frame_2.png");

    m_attackRightRects[0] = sf::IntRect(340, 0, 451, 452);
    m_attackRightRects[1] = sf::IntRect(336, 61, 432, 406);
    m_attackRightRects[2] = sf::IntRect(327, 80, 464, 374);
    m_attackLeftRects[0] = sf::IntRect(232, 0, 451, 452);
    m_attackLeftRects[1] = sf::IntRect(256, 61, 431, 405);
    m_attackLeftRects[2] = sf::IntRect(233, 80, 464, 373);

    m_normalScale = 0.2f;
    m_attackScale = 0.15f;
    m_attackFrameTime = 0.08f;
    m_attackTimer = 0.0f;
    m_attackFrame = 0;
    m_isAttacking = false;
    m_attackKeyWasPressed = false;
    m_horizontalDirection = Right;

    m_sprite.setTexture(m_frontTexture, true);
    m_sprite.setPosition(200.0f, 200.0f);
    m_sprite.setScale(m_normalScale, m_normalScale);
    m_speed = 250.0f;
}

void Player::handleInput(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (!m_isAttacking)
        {
            setNormalTexture(m_backTexture);
        }

        movement.y -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (!m_isAttacking)
        {
            setNormalTexture(m_frontTexture);
        }

        movement.y += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (!m_isAttacking)
        {
            m_horizontalDirection = Left;
            setNormalTexture(m_leftTexture);
        }

        movement.x -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (!m_isAttacking)
        {
            m_horizontalDirection = Right;
            setNormalTexture(m_rightTexture);
        }

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
    startAttack();
    updateAttack(deltaTime);
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

void Player::startAttack()
{
    const bool attackKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

    if (attackKeyPressed && !m_attackKeyWasPressed && !m_isAttacking)
    {
        m_isAttacking = true;
        m_attackTimer = 0.0f;
        m_attackFrame = 0;
        setAttackFrameTexture();
    }

    m_attackKeyWasPressed = attackKeyPressed;
}

void Player::updateAttack(float deltaTime)
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

        if (m_horizontalDirection == Left)
        {
            setNormalTexture(m_leftTexture);
        }
        else
        {
            setNormalTexture(m_rightTexture);
        }

        return;
    }

    setAttackFrameTexture();
}

void Player::setNormalTexture(sf::Texture& texture)
{
    setSpriteTexture(texture, m_normalScale);
}

void Player::setAttackFrameTexture()
{
    if (m_horizontalDirection == Left)
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

void Player::setSpriteTexture(sf::Texture& texture,
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
