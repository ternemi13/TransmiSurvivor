#pragma once

#include <SFML/Graphics.hpp>
#include <array>

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

    static const int ATTACK_FRAME_COUNT = 3;

    sf::Texture m_frontTexture;
    sf::Texture m_backTexture;
    sf::Texture m_leftTexture;
    sf::Texture m_rightTexture;
    std::array<sf::Texture, ATTACK_FRAME_COUNT> m_attackLeftTextures;
    std::array<sf::Texture, ATTACK_FRAME_COUNT> m_attackRightTextures;
    std::array<sf::IntRect, ATTACK_FRAME_COUNT> m_attackLeftRects;
    std::array<sf::IntRect, ATTACK_FRAME_COUNT> m_attackRightRects;
    sf::Sprite m_sprite;
    FacingDirection m_facingDirection;
    float m_normalScale;
    float m_attackScale;
    float m_speed;
    float m_attackRange;
    float m_attackFrameTime;
    float m_attackTimer;
    float m_attackCooldown;
    float m_attackCooldownTimer;
    int m_attackFrame;
    int m_attackId;
    int m_health;
    bool m_active;
    bool m_isAttacking;

    void setFacingDirection(FacingDirection facingDirection);
    void startAttack(FacingDirection attackDirection);
    void updateAttack(float deltaTime);
    void setAttackFrameTexture();
    void setSpriteTexture(sf::Texture& texture,
                          float scale,
                          sf::IntRect textureRect = sf::IntRect());

public:
    Enemy();

    bool spawn(const char* frontSpritePath,
               const char* backSpritePath,
               const char* leftSpritePath,
               const char* rightSpritePath,
               const char* attackLeftFrame0Path,
               const char* attackLeftFrame1Path,
               const char* attackLeftFrame2Path,
               const char* attackRightFrame0Path,
               const char* attackRightFrame1Path,
               const char* attackRightFrame2Path,
               sf::Vector2f position);
    void update(float deltaTime, sf::Vector2f targetPosition);
    void takeDamage(int damage);
    void render(sf::RenderWindow& window);
    bool isActive() const;
    bool isAttacking() const;
    bool isAttackDamageActive() const;
    int getAttackId() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getAttackBounds() const;
};
