#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "headers.hpp"
#include "object.hpp"

class entity : public object
{
protected:

    //HP
    uint8_t hp = 0;
    uint8_t max_hp = 0;

public:

    //CONSTRUCTROR
    using object::object;
    entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, uint8_t hp, uint8_t max_hp);

    void operator=(const entity& other);

    void setHP(uint8_t new_hp);

    void increaseHP(uint8_t delta);

    void decreaseHP(uint8_t delta);

    uint8_t getHP() const;
};

#endif // ENTITY_HPP