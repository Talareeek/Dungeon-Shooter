// Dungeon Shooter by Talareeek

// RenderableObject.cpp

#include "../include/RenderableObject.hpp"

#include "../include/headers.hpp"


RenderableObject::RenderableObject(sf::Vector2f size, sf::Texture* texture) : texture{texture}
{
    shape.setSize(size);
    shape.setTexture(texture);
}

RenderableObject::RenderableObject(sf::Texture* texture) : texture{texture}
{
    shape.setTexture(texture);
}

RenderableObject::RenderableObject()
{

}

void RenderableObject::setTexture(sf::Texture* texture)
{
    this->texture = texture;

    shape.setTexture(this->texture);
}

sf::Texture* RenderableObject::getTexture() const
{
    return texture;
}

void RenderableObject::setSize(sf::Vector2f size)
{
    shape.setSize(size);
}

sf::Vector2f RenderableObject::getSize() const
{
    return shape.getSize();
}

void RenderableObject::updateRender(const sf::Vector2f& position, float unit_size)
{
    shape.setPosition({position.x * unit_size, position.y * unit_size});
}

sf::RectangleShape& RenderableObject::getShape()
{
    return shape;
}