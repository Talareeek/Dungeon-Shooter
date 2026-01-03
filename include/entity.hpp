#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "headers.hpp"

class entity
{
private:

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Texture* texture;

    sf::RectangleShape rectangleshape;

    //HP
    uint8_t hp;
    uint8_t max_hp;

public:

    //CONSTRUCTROR
    entity();
    entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, uint8_t hp, uint8_t max_hp);

    void operator=(const entity& other);

    void updateRect();

    sf::RectangleShape& rectangle();

    //MOVEMENT
    void move(sf::Vector2f delta);

    void teleport(sf::Vector2f new_position);

    sf::Vector2f getPosition() const;

    void setHP(uint8_t new_hp);

    void increaseHP(uint8_t delta);

    void decreaseHP(uint8_t delta);

    uint8_t getHP() const;
};

#endif // ENTITY_HPP