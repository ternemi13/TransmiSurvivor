#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Transmi Survivor"),
      m_currentRoom(nullptr),
      m_deltaTime(0.0f),
      m_playerHealth(100.0f),
      m_playerMaxHealth(100.0f),
      m_wagonTravelTime(45.0f),
      m_wagonTravelTimer(0.0f),
      m_enemyCount(0),
      m_randomEngine(std::random_device{}())
{
    m_view.setSize(1280.0f, 720.0f);
    m_view.setCenter(640.0f, 360.0f);

    setupRooms();
    m_currentRoom = &m_entranceRoom;
    m_player.setPosition(sf::Vector2f(205.0f, 330.0f));
    m_view.setCenter(m_player.getPosition());
}

Game::~Game()
{
    m_currentRoom = nullptr;
}

void Game::setupRooms()
{
    const float segmentWidth = 409.6f;
    const float mapScale = 0.4f;
    const float doorInteriorScale = segmentWidth / 1125.0f;
    const sf::IntRect doorInteriorRect(68, 68, 1125, 1125);
    const float cabinRotation = 180.0f;
    const float wagonRotation = -90.0f;

    m_entranceRoom.setRoomType(Room::Entrance);
    m_entranceRoom.addSegment(
        "../assets/maps/station/entrance.png",
        0.0f,
        0.0f,
        mapScale
    );

    m_platformRoom.setRoomType(Room::Platform);
    m_platformRoom.addSegment(
        "../assets/maps/station/platform.png",
        0.0f,
        0.0f,
        mapScale
    );

    m_platformRoom.addSegment(
        "../assets/maps/station/platform.png",
        segmentWidth,
        0.0f,
        mapScale
    );

    m_platformRoom.addSegment(
        "../assets/maps/station/platform.png",
        segmentWidth * 2.0f,
        0.0f,
        mapScale
    );

    m_wagonRoom.setRoomType(Room::Wagon);
    m_wagonRoom.addSegment(
        "../assets/maps/wagon/cabin.png",
        0.0f,
        0.0f,
        mapScale,
        cabinRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interiorpuerta.png",
        segmentWidth,
        0.0f,
        doorInteriorScale,
        wagonRotation,
        doorInteriorRect
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interior.png",
        segmentWidth * 2.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interior.png",
        segmentWidth * 3.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/connector.png",
        segmentWidth * 4.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interior.png",
        segmentWidth * 5.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interiorpuerta.png",
        segmentWidth * 6.0f,
        0.0f,
        doorInteriorScale,
        wagonRotation,
        doorInteriorRect
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interior.png",
        segmentWidth * 7.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/connector.png",
        segmentWidth * 8.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interior.png",
        segmentWidth * 9.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interiorpuerta.png",
        segmentWidth * 10.0f,
        0.0f,
        doorInteriorScale,
        wagonRotation,
        doorInteriorRect
    );

    m_wagonRoom.addSegment(
        "../assets/maps/wagon/interior.png",
        segmentWidth * 11.0f,
        0.0f,
        mapScale,
        wagonRotation
    );

    m_doorArea = sf::FloatRect(
        150.0f,
        220.0f,
        110.0f,
        30.0f
    );

    const std::array<sf::FloatRect, 3> topDoorsInSegment = {
        sf::FloatRect(15.0f, 128.0f, 35.0f, 28.0f),
        sf::FloatRect(150.0f, 128.0f, 110.0f, 28.0f),
        sf::FloatRect(365.0f, 128.0f, 30.0f, 28.0f)
    };

    int doorIndex = 0;
    for (int segmentIndex = 0; segmentIndex < 3; segmentIndex++)
    {
        for (const sf::FloatRect& localDoor : topDoorsInSegment)
        {
            m_platformDoorAreas[doorIndex] = sf::FloatRect(
                localDoor.left + segmentWidth * segmentIndex,
                localDoor.top,
                localDoor.width,
                localDoor.height
            );

            doorIndex++;
        }
    }
}

void Game::changeToPlatformRoom()
{
    m_currentRoom = &m_platformRoom;
    m_player.setPosition(sf::Vector2f(200.0f, 200.0f));
    m_view.setCenter(m_player.getPosition());
}

void Game::changeToWagonRoom(int platformDoorIndex)
{
    const float segmentWidth = 409.6f;
    const float spawnY = 210.0f;

    m_currentRoom = &m_wagonRoom;

    const std::array<int, 3> doorInteriorSegments = {1, 6, 10};
    const int doorInteriorIndex = platformDoorIndex / 3;
    const float interiorStartX = segmentWidth * doorInteriorSegments[doorInteriorIndex];

    m_player.setPosition(sf::Vector2f(interiorStartX + 200.0f, spawnY));
    m_wagonTravelTimer = m_wagonTravelTime;
    spawnWagonEnemies();

    m_view.setCenter(m_player.getPosition());
}

void Game::spawnWagonEnemies()
{
    const float segmentWidth = 409.6f;
    const std::array<int, 9> interiorSegments = {1, 2, 3, 5, 6, 7, 9, 10, 11};
    const std::array<const char*, 2> enemySprites = {
        "../assets/sprites/enemies/enemie1/front.png",
        "../assets/sprites/enemies/enemie2/front.png"
    };

    std::uniform_int_distribution<int> segmentDistribution(0, interiorSegments.size() - 1);
    std::uniform_int_distribution<int> enemyDistribution(0, enemySprites.size() - 1);
    std::uniform_real_distribution<float> xDistribution(120.0f, 285.0f);
    std::uniform_real_distribution<float> yDistribution(135.0f, 290.0f);

    m_enemyCount = MAX_ENEMIES;

    for (int i = 0; i < m_enemyCount; i++)
    {
        const int segmentIndex = interiorSegments[segmentDistribution(m_randomEngine)];
        const sf::Vector2f enemyPosition(
            segmentWidth * segmentIndex + xDistribution(m_randomEngine),
            yDistribution(m_randomEngine)
        );

        m_enemies[i].spawn(
            enemySprites[enemyDistribution(m_randomEngine)],
            enemyPosition
        );
    }
}

void Game::run()
{
    while (m_window.isOpen())
    {
        m_deltaTime = m_clock.restart().asSeconds();
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
}

void Game::update()
{
    sf::Vector2f oldPosition = m_player.getPosition();

    m_player.update(m_deltaTime);

    sf::FloatRect playerBounds = m_player.getBounds();
    const sf::Vector2f playerFeet(
        playerBounds.left + playerBounds.width * 0.5f,
        playerBounds.top + playerBounds.height
    );
    sf::FloatRect playableArea = m_currentRoom->getPlayableArea();

    const bool outsidePlayableArea =
        playerBounds.left < playableArea.left ||
        playerBounds.top < playableArea.top ||
        playerBounds.left + playerBounds.width >
            playableArea.left + playableArea.width ||
        playerBounds.top + playerBounds.height >
            playableArea.top + playableArea.height;

    if (outsidePlayableArea)
    {
        m_player.setPosition(oldPosition);
    }

    if (m_currentRoom->getRoomType() == Room::Entrance)
    {
        if (m_player.getBounds().intersects(m_doorArea))
        {
            changeToPlatformRoom();
        }
    }
    else if (m_currentRoom->getRoomType() == Room::Platform)
    {
        for (int doorIndex = 0; doorIndex < PLATFORM_DOOR_COUNT; doorIndex++)
        {
            if (m_platformDoorAreas[doorIndex].contains(playerFeet))
            {
                changeToWagonRoom(doorIndex);
                break;
            }
        }
    }

    if (m_currentRoom->getRoomType() == Room::Wagon && m_wagonTravelTimer > 0.0f)
    {
        m_wagonTravelTimer -= m_deltaTime;

        if (m_wagonTravelTimer < 0.0f)
        {
            m_wagonTravelTimer = 0.0f;
        }
    }

    m_view.setCenter(m_player.getPosition());
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_window.setView(m_view);
    m_currentRoom->render(m_window);

    if (m_currentRoom->getRoomType() == Room::Wagon)
    {
        for (int i = 0; i < m_enemyCount; i++)
        {
            m_enemies[i].render(m_window);
        }
    }

    m_player.render(m_window);

    m_window.setView(m_window.getDefaultView());
    m_renderer.renderHud(
        m_window,
        m_playerHealth / m_playerMaxHealth,
        m_currentRoom->getRoomType() == Room::Wagon,
        m_wagonTravelTimer / m_wagonTravelTime
    );

    m_window.display();
}
