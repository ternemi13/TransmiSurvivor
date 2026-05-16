#include "Room.h"

Room::Room()
{
    m_segmentCount = 0;
    m_playableArea = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
}

void Room::addSegment(const char* path,
                      float x,
                      float y,
                      float scale,
                      float rotation)
{
    if (m_segmentCount >= MAX_SEGMENTS)
    {
        return;
    }

    if (!m_mapTextures[m_segmentCount].loadFromFile(path))
    {
        return;
    }

    sf::Sprite& sprite = m_mapSprites[m_segmentCount];
    sf::Texture& texture = m_mapTextures[m_segmentCount];

    sprite.setTexture(
        m_mapTextures[m_segmentCount]
    );

    sprite.setScale(scale, scale);

    if (rotation != 0.0f)
    {
        const sf::Vector2u textureSize = texture.getSize();
        const float scaledWidth = static_cast<float>(textureSize.x) * scale;
        const float scaledHeight = static_cast<float>(textureSize.y) * scale;

        sprite.setOrigin(
            static_cast<float>(textureSize.x) * 0.5f,
            static_cast<float>(textureSize.y) * 0.5f
        );

        sprite.setPosition(
            x + scaledWidth * 0.5f,
            y + scaledHeight * 0.5f
        );

        sprite.setRotation(rotation);
    }
    else
    {
        sprite.setPosition(x, y);
    }

    sf::FloatRect segmentBounds = sprite.getGlobalBounds();

    if (m_segmentCount == 0)
    {
        m_playableArea = segmentBounds;
    }
    else
    {
        float left = m_playableArea.left;
        float top = m_playableArea.top;
        float right = m_playableArea.left + m_playableArea.width;
        float bottom = m_playableArea.top + m_playableArea.height;

        float segmentRight = segmentBounds.left + segmentBounds.width;
        float segmentBottom = segmentBounds.top + segmentBounds.height;

        if (segmentBounds.left < left)
        {
            left = segmentBounds.left;
        }

        if (segmentBounds.top < top)
        {
            top = segmentBounds.top;
        }

        if (segmentRight > right)
        {
            right = segmentRight;
        }

        if (segmentBottom > bottom)
        {
            bottom = segmentBottom;
        }

        m_playableArea = sf::FloatRect(left, top, right - left, bottom - top);
    }

    m_segmentCount++;
}

void Room::render(sf::RenderWindow& window)
{
    for (int i = 0; i < m_segmentCount; i++)
    {
        window.draw(m_mapSprites[i]);
    }
}

sf::FloatRect Room::getPlayableArea() const
{
    return m_playableArea;
}

void Room::setRoomType(RoomType type)
{
    m_roomType = type;
}

Room::RoomType Room::getRoomType() const
{
    return m_roomType;
}
