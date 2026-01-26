// DUNGEON SHOOTER by Talareeek

// WorldObject.hpp

#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "headers.hpp"

class WorldObject
{
protected:

    sf::Vector2f position{0.0f, 0.0f};
    sf::Vector2f size{1.0f, 1.0f};

public:

    WorldObject();
    WorldObject(sf::Vector2f position, sf::Vector2f size);

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    sf::Vector2f getSize() const;

    void setSize(sf::Vector2f size);

    bool collides(WorldObject& other);

};

#endif // WORLD_OBJECT_HPP