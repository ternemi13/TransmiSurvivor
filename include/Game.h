#pragma once

#include <array>
#include <random>

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "Room.h"

class Game
{
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::View m_view;
    Renderer m_renderer;
    sf::FloatRect m_doorArea;
    static const int PLATFORM_DOOR_COUNT = 9;
    static const int WAGON_DOOR_COUNT = 3;
    static const int MAX_ENEMIES = 8;
    std::array<sf::FloatRect, PLATFORM_DOOR_COUNT> m_platformDoorAreas;
    std::array<sf::FloatRect, WAGON_DOOR_COUNT> m_wagonExitDoorAreas;
    std::array<Enemy, MAX_ENEMIES> m_enemies;
    std::array<int, MAX_ENEMIES> m_enemyLastHitAttackIds;
    std::array<int, MAX_ENEMIES> m_enemyLastPlayerDamageAttackIds;

    Room m_entranceRoom;
    Room m_platformRoom;
    Room* m_currentRoom;

    Room m_wagonRoom;

    float m_deltaTime;
    float m_playerHealth;
    float m_playerMaxHealth;
    float m_wagonTravelTime;
    float m_wagonTravelTimer;
    float m_enemyAttackDamage;
    float m_platformBoardingCooldownTimer;
    int m_playerAttackDamage;
    int m_enemyCount;
    std::mt19937 m_randomEngine;

    Player m_player;

    void processEvents();

    void update();

    void render();

    void setupRooms();

    void changeToPlatformRoom();
    void changeToPlatformRoomFromWagon(int wagonDoorIndex);
    void changeToWagonRoom(int platformDoorIndex);
    void spawnWagonEnemies();
    int countAliveWagonEnemies() const;
    bool areWagonEnemiesDefeated() const;

public:
    Game();
    ~Game();

    void run();
};
