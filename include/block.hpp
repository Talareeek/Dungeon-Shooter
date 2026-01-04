#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "headers.hpp"
#include "object.hpp"

class block : public object
{
public:

    using object::object;

    void update();

    static block Air(sf::Vector2f position);

    static block Wall(sf::Vector2f position);

    static block Floor(sf::Vector2f position);

    static block Spawner(sf::Vector2f position);

};

#endif // BLOCK_HPP