#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(1280, 720), "Transmi Survivor")
{
    m_view.setSize(1280.0f, 720.0f);

    m_view.setCenter(640.0f, 360.0f);

    m_mapTexture.loadFromFile("../assets/maps/station.png");

m_mapSprite.setTexture(m_mapTexture);

m_mapSprite.setScale(0.4f, 0.4f);

   m_floor.setSize(sf::Vector2f(2000.0f, 2000.0f));

m_floor.setFillColor(sf::Color(50, 50, 50));

m_floor.setPosition(-1000.0f, -1000.0f);



m_topWall.setSize(sf::Vector2f(2000.0f, 100.0f));

m_topWall.setFillColor(sf::Color(120, 20, 20));

m_topWall.setPosition(-1000.0f, -1000.0f);



m_bottomWall.setSize(sf::Vector2f(2000.0f, 100.0f));

m_bottomWall.setFillColor(sf::Color(120, 20, 20));

m_bottomWall.setPosition(-1000.0f, 1900.0f);



m_leftWall.setSize(sf::Vector2f(100.0f, 2000.0f));

m_leftWall.setFillColor(sf::Color(120, 20, 20));

m_leftWall.setPosition(-1000.0f, -1000.0f);



m_rightWall.setSize(sf::Vector2f(100.0f, 2000.0f));

m_rightWall.setFillColor(sf::Color(120, 20, 20));

m_rightWall.setPosition(1900.0f, -1000.0f);
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
    //m_player.update(m_deltaTime);

    sf::Vector2f oldPosition = m_player.getPosition();

m_player.update(m_deltaTime);



if (m_player.getBounds().intersects(m_topWall.getGlobalBounds()) ||
    m_player.getBounds().intersects(m_bottomWall.getGlobalBounds()) ||
    m_player.getBounds().intersects(m_leftWall.getGlobalBounds()) ||
    m_player.getBounds().intersects(m_rightWall.getGlobalBounds()))
{
    m_player.setPosition(oldPosition);
}



m_view.setCenter(m_player.getPosition());
    m_view.setCenter(m_player.getPosition());
}
void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_window.setView(m_view);
    m_window.draw(m_mapSprite);

//m_window.draw(m_floor);

//m_window.draw(m_topWall);

//m_window.draw(m_bottomWall);

//m_window.draw(m_leftWall);

//m_window.draw(m_rightWall);


 m_player.render(m_window);
    m_window.display();
}
