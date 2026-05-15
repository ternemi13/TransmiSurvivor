#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Transmi Survivor"),
      m_currentRoom(nullptr),
      m_deltaTime(0.0f)
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
    m_entranceRoom.setRoomType(Room::Entrance);
    m_entranceRoom.addSegment(
        "../assets/maps/station/entrance.png",
        0.0f,
        0.0f,
        0.4f
    );

    m_platformRoom.setRoomType(Room::Platform);
    m_platformRoom.addSegment(
        "../assets/maps/station/platform.png",
        0.0f,
        0.0f,
        0.4f
    );

    m_platformRoom.addSegment(
        "../assets/maps/station/platform.png",
        409.6f,
        0.0f,
        0.4f
    );

    m_platformRoom.addSegment(
        "../assets/maps/station/platform.png",
        819.2f,
        0.0f,
        0.4f
    );

    m_doorArea = sf::FloatRect(
        150.0f,
        220.0f,
        110.0f,
        30.0f
    );
}

void Game::changeToPlatformRoom()
{
    m_currentRoom = &m_platformRoom;
    m_player.setPosition(sf::Vector2f(200.0f, 200.0f));
    m_view.setCenter(m_player.getPosition());
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

    m_view.setCenter(m_player.getPosition());
    if (m_currentRoom->getRoomType() == Room::Entrance)
    {
        if (m_player.getBounds().intersects(m_doorArea))
        {
            changeToPlatformRoom();
        }
    }
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_window.setView(m_view);
    m_currentRoom->render(m_window);
    m_player.render(m_window);
    m_window.display();
}
