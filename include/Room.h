#pragma once

#include <SFML/Graphics.hpp>

class Room
{

public:

            enum RoomType
{
    Entrance,
    Platform,
    Wagon
};


private:
    static const int MAX_SEGMENTS = 20;

    sf::FloatRect m_playableArea;
    sf::Texture m_mapTextures[MAX_SEGMENTS];
    sf::Sprite m_mapSprites[MAX_SEGMENTS];
    int m_segmentCount;
 
   RoomType m_roomType;
public:
    Room();

 


    void render(sf::RenderWindow& window);
    sf::FloatRect getPlayableArea() const;

    void addSegment(const char* path,
                float x,
                float y,
                float scale,
                float rotation = 0.0f,
                sf::IntRect textureRect = sf::IntRect());

    
void setRoomType(RoomType type);

RoomType getRoomType() const;
};
