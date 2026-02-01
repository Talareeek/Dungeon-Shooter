//DEPRECATED

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"

class object
{
protected:

    sf::Vector2f position{0.0f, 0.0f};
    sf::Vector2f size{1.0f, 1.0f};
    sf::Texture* texture = nullptr;

    sf::RectangleShape rectangleshape;

public:

    object();
    object(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture);

    void operator=(const object& other);

    virtual void update();

    sf::RectangleShape& rectangle();

    void move(sf::Vector2f delta);

    void teleport(sf::Vector2f new_position);

    sf::Vector2f getPosition() const;

    bool isNULL() const;

    explicit operator bool() const;

    bool collides(object& other);

    //OPERATORS
    bool operator==(const object& other) const;

};

#endif // OBJECT_HPP