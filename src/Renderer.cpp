#include "Renderer.h"

#include <algorithm>

void Renderer::renderHud(sf::RenderWindow& window,
                         float healthRatio,
                         bool showTravelTimer,
                         float travelRatio,
                         bool showPlatformTimer,
                         float platformRatio,
                         int aliveEnemyCount,
                         int maxEnemyCount)
{
    const sf::Vector2u windowSize = window.getSize();
    const float windowWidth = static_cast<float>(windowSize.x);
    const float windowHeight = static_cast<float>(windowSize.y);

    drawBar(
        window,
        sf::Vector2f(36.0f, windowHeight - 42.0f),
        sf::Vector2f(260.0f, 16.0f),
        healthRatio,
        sf::Color(205, 36, 36),
        sf::Color(54, 18, 18),
        sf::Color(235, 195, 195)
    );

    if (showTravelTimer)
    {
        drawBar(
            window,
            sf::Vector2f((windowWidth - 520.0f) * 0.5f, 22.0f),
            sf::Vector2f(520.0f, 14.0f),
            travelRatio,
            sf::Color(242, 195, 44),
            sf::Color(45, 40, 24),
            sf::Color(245, 224, 142)
        );

        const float enemyCounterWidth = std::max(
            132.0f,
            84.0f + static_cast<float>(maxEnemyCount) * 16.0f
        );
        drawEnemyCounter(
            window,
            sf::Vector2f(windowWidth - enemyCounterWidth - 36.0f, windowHeight - 49.0f),
            aliveEnemyCount,
            maxEnemyCount
        );
    }
    else if (showPlatformTimer)
    {
        drawBar(
            window,
            sf::Vector2f((windowWidth - 520.0f) * 0.5f, 22.0f),
            sf::Vector2f(520.0f, 14.0f),
            platformRatio,
            sf::Color(55, 160, 245),
            sf::Color(18, 35, 52),
            sf::Color(150, 220, 255)
        );
    }
}

void Renderer::drawBar(sf::RenderWindow& window,
                       sf::Vector2f position,
                       sf::Vector2f size,
                       float ratio,
                       sf::Color fillColor,
                       sf::Color backColor,
                       sf::Color outlineColor)
{
    const float clampedRatio = std::clamp(ratio, 0.0f, 1.0f);

    sf::RectangleShape background(size);
    background.setPosition(position);
    background.setFillColor(backColor);
    background.setOutlineThickness(2.0f);
    background.setOutlineColor(outlineColor);

    sf::RectangleShape fill(sf::Vector2f(size.x * clampedRatio, size.y));
    fill.setPosition(position);
    fill.setFillColor(fillColor);

    window.draw(background);
    window.draw(fill);
}

void Renderer::drawEnemyCounter(sf::RenderWindow& window,
                                sf::Vector2f position,
                                int aliveEnemyCount,
                                int maxEnemyCount)
{
    const int clampedMax = std::clamp(maxEnemyCount, 0, 12);
    const int clampedAlive = std::clamp(aliveEnemyCount, 0, clampedMax);
    const float width = std::max(
        132.0f,
        84.0f + static_cast<float>(clampedMax) * 16.0f
    );

    sf::RectangleShape background(sf::Vector2f(width, 28.0f));
    background.setPosition(position);
    background.setFillColor(sf::Color(18, 14, 14, 205));
    background.setOutlineThickness(2.0f);
    background.setOutlineColor(sf::Color(175, 72, 72));
    window.draw(background);

    for (int i = 0; i < clampedMax; i++)
    {
        sf::CircleShape marker(5.0f);
        marker.setPosition(
            position.x + 14.0f + static_cast<float>(i) * 16.0f,
            position.y + 9.0f
        );

        if (i < clampedAlive)
        {
            marker.setFillColor(sf::Color(215, 32, 32));
            marker.setOutlineColor(sf::Color(255, 118, 118));
        }
        else
        {
            marker.setFillColor(sf::Color(56, 22, 22));
            marker.setOutlineColor(sf::Color(92, 42, 42));
        }

        marker.setOutlineThickness(1.0f);
        window.draw(marker);
    }

    drawNumber(
        window,
        sf::Vector2f(position.x + width - 34.0f, position.y + 4.0f),
        clampedAlive,
        0.85f,
        sf::Color(255, 222, 222)
    );
}

void Renderer::drawNumber(sf::RenderWindow& window,
                          sf::Vector2f position,
                          int number,
                          float scale,
                          sf::Color color)
{
    const int clampedNumber = std::clamp(number, 0, 99);
    const float digitWidth = 14.0f * scale;
    const float spacing = 5.0f * scale;

    if (clampedNumber >= 10)
    {
        drawDigit(window, position, clampedNumber / 10, scale, color);
        drawDigit(
            window,
            sf::Vector2f(position.x + digitWidth + spacing, position.y),
            clampedNumber % 10,
            scale,
            color
        );
        return;
    }

    drawDigit(window, position, clampedNumber, scale, color);
}

void Renderer::drawDigit(sf::RenderWindow& window,
                         sf::Vector2f position,
                         int digit,
                         float scale,
                         sf::Color color)
{
    const bool segments[10][7] = {
        {true, true, true, true, true, true, false},
        {false, true, true, false, false, false, false},
        {true, true, false, true, true, false, true},
        {true, true, true, true, false, false, true},
        {false, true, true, false, false, true, true},
        {true, false, true, true, false, true, true},
        {true, false, true, true, true, true, true},
        {true, true, true, false, false, false, false},
        {true, true, true, true, true, true, true},
        {true, true, true, true, false, true, true}
    };
    const int clampedDigit = std::clamp(digit, 0, 9);
    const float unit = scale;
    const sf::Vector2f horizontalSize(10.0f * unit, 2.0f * unit);
    const sf::Vector2f verticalSize(2.0f * unit, 8.0f * unit);

    if (segments[clampedDigit][0])
    {
        drawSegment(window, sf::Vector2f(position.x + 2.0f * unit, position.y), horizontalSize, color);
    }

    if (segments[clampedDigit][1])
    {
        drawSegment(window, sf::Vector2f(position.x + 12.0f * unit, position.y + 2.0f * unit), verticalSize, color);
    }

    if (segments[clampedDigit][2])
    {
        drawSegment(window, sf::Vector2f(position.x + 12.0f * unit, position.y + 12.0f * unit), verticalSize, color);
    }

    if (segments[clampedDigit][3])
    {
        drawSegment(window, sf::Vector2f(position.x + 2.0f * unit, position.y + 20.0f * unit), horizontalSize, color);
    }

    if (segments[clampedDigit][4])
    {
        drawSegment(window, sf::Vector2f(position.x, position.y + 12.0f * unit), verticalSize, color);
    }

    if (segments[clampedDigit][5])
    {
        drawSegment(window, sf::Vector2f(position.x, position.y + 2.0f * unit), verticalSize, color);
    }

    if (segments[clampedDigit][6])
    {
        drawSegment(window, sf::Vector2f(position.x + 2.0f * unit, position.y + 10.0f * unit), horizontalSize, color);
    }
}

void Renderer::drawSegment(sf::RenderWindow& window,
                           sf::Vector2f position,
                           sf::Vector2f size,
                           sf::Color color)
{
    sf::RectangleShape segment(size);
    segment.setPosition(position);
    segment.setFillColor(color);
    window.draw(segment);
}
