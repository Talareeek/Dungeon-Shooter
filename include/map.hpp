#ifndef MAP_HPP
#define MAP_HPP

#include "headers.hpp"
#include "chunk.hpp"

class map
{
public:

    chunk chunks[128][128];

public:

    map();

    void generate();

    void draw(sf::RenderWindow& window, sf::Vector2f position);

    bool collides(object& object_);

};

#endif // MAP_HPP