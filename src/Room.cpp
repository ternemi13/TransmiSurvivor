#include "Room.h"

Room::Room()
{
    m_segmentCount = 0;
    m_playableArea = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
}

void Room::addSegment(const char* path,
                      float x,
                      float y,
                      float scale)
{
    if (m_segmentCount >= MAX_SEGMENTS)
    {
        return;
    }

    if (!m_mapTextures[m_segmentCount].loadFromFile(path))
    {
        return;
    }

    m_mapSprites[m_segmentCount].setTexture(
        m_mapTextures[m_segmentCount]
    );

    m_mapSprites[m_segmentCount].setPosition(x, y);

    m_mapSprites[m_segmentCount].setScale(scale, scale);

    sf::FloatRect segmentBounds = m_mapSprites[m_segmentCount].getGlobalBounds();

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