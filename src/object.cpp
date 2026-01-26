//DEPRECATED

#include "../include/headers.hpp"
#include "../include/object.hpp"

extern unsigned int unit_size;

object::object()
{
    rectangleshape.setSize(size);
    rectangleshape.setScale({unit_size / size.x, unit_size / size.y});
    rectangleshape.setTexture(texture);
    rectangleshape.setTextureRect({{0, 0}, {16, 16}});
}


object::object(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture) : position{position}, size{size}, texture{texture}
{
    rectangleshape.setSize(size);
    rectangleshape.setScale({unit_size / size.x, unit_size / size.y});
    rectangleshape.setTexture(texture);
    rectangleshape.setTextureRect({{0, 0}, {16, 16}});
}

void object::operator=(const object& other)
{
    size = other.size;
    position = other.position;
    texture = other.texture;
    update();
}

void object::update()
{
    rectangleshape.setSize(size);
    rectangleshape.setScale({unit_size / size.x, unit_size / size.y});
    rectangleshape.setTexture(texture);
    rectangleshape.setPosition({position.x * unit_size, position.y * unit_size});
}

sf::RectangleShape& object::rectangle()
{
    return rectangleshape;
}

void object::move(sf::Vector2f delta)
{
    position += delta;
}

void object::teleport(sf::Vector2f new_position)
{
    position = new_position;
}

sf::Vector2f object::getPosition() const
{
    return position;
}

bool object::isNULL() const
{
    if(texture == nullptr) return true;
    else return false;
}

object::operator bool() const
{
    return !isNULL();
}

bool object::collides(object& other)
{
    sf::FloatRect this_rect(position, size);
    sf::FloatRect other_rect(other.position, other.size);

    std::optional<sf::FloatRect> intersection = this_rect.findIntersection(other_rect);
    return intersection.has_value();
}

bool object::operator==(const object& other) const
{
    return (position == other.position && size == other.size && texture == other.texture);
}