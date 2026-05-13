#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

    sf::RenderWindow m_window;
    sf::Clock m_clock;

float m_deltaTime;

    Player m_player;

    void processEvents();

    void update();

    void render();

public:

    Game();

    void run();
};
