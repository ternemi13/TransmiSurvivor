#pragma once

#include <array>

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
    static const int PLATFORM_DOOR_COUNT = 9;
    std::array<sf::FloatRect, PLATFORM_DOOR_COUNT> m_platformDoorAreas;

    Room m_entranceRoom;
    Room m_platformRoom;
    Room* m_currentRoom;

    Room m_wagonRoom;

    float m_deltaTime;

    Player m_player;

    void processEvents();

    void update();

    void render();

    void setupRooms();

    void changeToPlatformRoom();
    void changeToWagonRoom(int platformDoorIndex);

public:
    Game();
    ~Game();

    void run();
};
