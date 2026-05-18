#pragma once

#include <array>

#include <SFML/Graphics.hpp>

class Player
{
private:
    enum HorizontalDirection
    {
        Left,
        Right
    };

    static const int ATTACK_FRAME_COUNT = 3;

    sf::Texture m_frontTexture;
    sf::Texture m_backTexture;
    sf::Texture m_leftTexture;
    sf::Texture m_rightTexture;
    sf::Texture m_guardLeftTexture;
    sf::Texture m_guardRightTexture;
    std::array<sf::Texture, ATTACK_FRAME_COUNT> m_attackLeftTextures;
    std::array<sf::Texture, ATTACK_FRAME_COUNT> m_attackRightTextures;
    sf::IntRect m_guardLeftRect;
    sf::IntRect m_guardRightRect;
    std::array<sf::IntRect, ATTACK_FRAME_COUNT> m_attackLeftRects;
    std::array<sf::IntRect, ATTACK_FRAME_COUNT> m_attackRightRects;
    sf::Sprite m_sprite;
    float m_speed;
    float m_normalScale;
    float m_guardScale;
    float m_attackScale;
    float m_attackFrameTime;
    float m_attackTimer;
    int m_attackFrame;
    int m_attackId;
    bool m_isAttacking;
    bool m_isGuarding;
    bool m_attackKeyWasPressed;
    HorizontalDirection m_horizontalDirection;

    void startAttack();
    void updateAttack(float deltaTime);
    void setNormalTexture(sf::Texture& texture);
    void setGuardTexture();
    void setAttackFrameTexture();
    void setSpriteTexture(sf::Texture& texture,
                          float scale,
                          sf::IntRect textureRect = sf::IntRect());

public:
    Player();

    void setPosition(sf::Vector2f position);
    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getAttackBounds() const;
    bool isAttacking() const;
    bool isGuarding() const;
    int getAttackId() const;
};
