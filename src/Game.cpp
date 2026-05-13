#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Transmi Survivor")
{
}

void Game::run()
{
    while (m_window.isOpen())
    {
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
    m_player.update();
}
void Game::render()
{
    m_window.clear(sf::Color::Black);
 m_player.render(m_window);
    m_window.display();
}
