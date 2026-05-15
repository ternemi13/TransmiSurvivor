#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Room.h"

class Game
{
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::View m_view;
    sf::FloatRect m_doorArea;

    Room m_entranceRoom;
    Room m_platformRoom;
    Room* m_currentRoom;
    float m_deltaTime;

    Player m_player;

    void processEvents();

    void update();

    void render();

    void setupRooms();

    void changeToPlatformRoom();

public:
    Game();
    ~Game();

    void run();
};
