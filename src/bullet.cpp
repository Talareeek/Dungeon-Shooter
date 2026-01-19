#include "../include/bullet.hpp"
#include "../include/headers.hpp"

extern unsigned int unit_size;

bullet::bullet(sf::Vector2f position, sf::Texture* texture, uint8_t damage, float direction_angle, float speed) : object(position, {0.25, 0.25}, texture)
{
    this->direction_angle = direction_angle;
    this->speed = speed;
    this->damage = damage;

    rectangleshape.setTextureRect(sf::IntRect({0, 0}, {8, 8}));

    sf::Angle angle = sf::radians(direction_angle);

    rectangleshape.setRotation(angle);
}

void bullet::update()
{
    move({(std::cos(direction_angle) * speed) * (1.0f/60.0f), (std::sin(direction_angle) * speed) * (1.0f/60.0f)});

    object::update();
}