#include "../include/projectile.hpp"
#include "../include/headers.hpp"

extern unsigned int unit_size;

projectile::projectile(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, uint8_t damage, float direction_angle, float speed) : entity(position, size, texture, 1, 1)
{
    this->direction_angle = direction_angle;
    this->speed = speed;
    this->damage = damage;

    sf::Angle angle = sf::radians(direction_angle);

    rectangleshape.setRotation(angle);
}

void projectile::update()
{
    move({(std::cos(direction_angle) * speed) * (1.0f/60.0f), (std::sin(direction_angle) * speed) * (1.0f/60.0f)});

    object::update();
}