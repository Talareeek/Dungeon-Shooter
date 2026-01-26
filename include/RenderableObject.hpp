// Dungeon Shooter by Talareeek_

// RenderableObject.hpp

#ifndef RENDERABLE_OBJECT_HPP
#define RENDERABLE_OBJECT_HPP

#include "headers.hpp"

class RenderableObject
{
protected:

    sf::RectangleShape shape;
    sf::Texture* texture = nullptr;

public:

    RenderableObject(sf::Vector2f size, sf::Texture* texture);
    RenderableObject(sf::Texture* texture);
    RenderableObject();

    void setTexture(sf::Texture* texture);
    sf::Texture* getTexture() const;

    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;

    void updateRender(const sf::Vector2f& worldPosition, float unit_size);

    sf::RectangleShape& getShape();
};

#endif // RENDERABLE_OBJECT_HPP