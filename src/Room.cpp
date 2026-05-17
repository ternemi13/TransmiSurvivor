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
                      float rotation,
                      sf::IntRect textureRect)
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

    sprite.setTexture(
        m_mapTextures[m_segmentCount]
    );

    if (textureRect.width > 0 && textureRect.height > 0)
    {
        sprite.setTextureRect(textureRect);
    }

    sprite.setScale(scale, scale);

    if (rotation != 0.0f)
    {
        const sf::FloatRect localBounds = sprite.getLocalBounds();

        sprite.setOrigin(
            localBounds.left + localBounds.width * 0.5f,
            localBounds.top + localBounds.height * 0.5f
        );

        sprite.setPosition(x, y);
        sprite.setRotation(rotation);

        const sf::FloatRect rotatedBounds = sprite.getGlobalBounds();
        sprite.move(x - rotatedBounds.left, y - rotatedBounds.top);
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
