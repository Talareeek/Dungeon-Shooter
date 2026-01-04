#include "..\include\headers.hpp"
#include "..\include\entity.hpp"

extern unsigned int unit_size;
extern bool random_tick;


entity::entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, uint8_t hp, uint8_t max_hp) : entity(position, size, texture)
{
    this->hp = hp;
    this->max_hp = max_hp;
}

void entity::operator=(const entity& other)
{
    position = other.position;
    size = other.size;
    texture = other.texture;
    rectangleshape = other.rectangleshape;
    hp = other.hp;
    max_hp = other.max_hp;
}

void entity::setHP(uint8_t new_hp)
{
    if(new_hp > max_hp)
    {
        new_hp = max_hp;
    }
    hp = new_hp;
}

void entity::increaseHP(uint8_t delta)
{
    setHP(hp + delta);
}

void entity::decreaseHP(uint8_t delta)
{
    if(delta >= hp)
    {
        hp = 0;
    }
    else
    {
        hp -= delta;
    }
}

uint8_t entity::getHP() const
{
    return hp;
}