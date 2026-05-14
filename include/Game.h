#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::View m_view;

    sf::RectangleShape m_floor;

sf::RectangleShape m_topWall;

sf::RectangleShape m_bottomWall;

sf::RectangleShape m_leftWall;

sf::RectangleShape m_rightWall;

sf::Texture m_mapTexture;

sf::Sprite m_mapSprite;

float m_deltaTime;

    Player m_player;

    void processEvents();

    void update();

    void render();

public:

    Game();

    void run();
};
