#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Transmi Survivor")
{
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
    m_player.update(m_deltaTime);
}
void Game::render()
{
    m_window.clear(sf::Color::Black);
 m_player.render(m_window);
    m_window.display();
}
