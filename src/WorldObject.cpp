//DUNGEON SHOOTER by Talareeek

// WorldObject.cpp

#include "../include/WorldObject.hpp"
#include "../include/headers.hpp"

WorldObject::WorldObject()
{

}

WorldObject::WorldObject(sf::Vector2f position, sf::Vector2f size) : position{position}, size{size}
{

}

sf::Vector2f WorldObject::getPosition() const
{
    return position;
}

void WorldObject::setPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f WorldObject::getSize() const
{
    return size;
}

void WorldObject::setSize(sf::Vector2f size)
{
    this->size = size;
}

bool WorldObject::collides(WorldObject& other)
{
    sf::FloatRect this_rect(position, size);
    sf::FloatRect other_rect(other.position, other.size);

    std::optional<sf::FloatRect> intersection = this_rect.findIntersection(other_rect);
    return intersection.has_value();
}