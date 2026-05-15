#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Transmi Survivor")
{
    m_view.setSize(1280.0f, 720.0f);

    m_view.setCenter(640.0f, 360.0f);

    m_mapTexture.loadFromFile("../assets/maps/station.png");
    m_mapSprite.setTexture(m_mapTexture);
    m_mapSprite.setScale(0.4f, 0.4f);

    const sf::FloatRect mapBounds = m_mapSprite.getGlobalBounds();
    m_playableArea = sf::FloatRect(
        mapBounds.left + 20.0f,
        mapBounds.top + 132.0f,
        mapBounds.width - 40.0f,
        148.0f
    );

    m_player.setPosition(sf::Vector2f(
        m_playableArea.left + (m_playableArea.width * 0.5f),
        m_playableArea.top + (m_playableArea.height * 0.5f)
    ));
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
    const bool outsidePlayableArea =
        playerBounds.left < m_playableArea.left ||
        playerBounds.top < m_playableArea.top ||
        playerBounds.left + playerBounds.width > m_playableArea.left + m_playableArea.width ||
        playerBounds.top + playerBounds.height > m_playableArea.top + m_playableArea.height;

    if (outsidePlayableArea)
    {
        m_player.setPosition(oldPosition);
    }

    m_view.setCenter(m_player.getPosition());
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_window.setView(m_view);
    m_window.draw(m_mapSprite);
    m_player.render(m_window);
    m_window.display();
}
