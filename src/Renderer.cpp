#include "Renderer.h"

#include <algorithm>

void Renderer::renderHud(sf::RenderWindow& window,
                         float healthRatio,
                         bool showTravelTimer,
                         float travelRatio)
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
