#ifndef PROGECTILE_HPP
#define PROGECTILE_HPP

#include "entity.hpp"
#include "headers.hpp"

class projectile : public entity
{
private:

    uint8_t damage;
    float speed;
    float direction_angle;

public:

    projectile(sf::Vector2f position, sf::Texture* texture, uint8_t damage, float direction_angle, float speed);

    void update();
};

#endif // PROGECTILE_HPP