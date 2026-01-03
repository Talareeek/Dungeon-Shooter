#include "..\include\headers.hpp"
#include "..\include\entity.hpp"

extern unsigned int unit_size;
extern bool random_tick;

entity::entity() : position{0,0}, size{16,16}, texture{nullptr}, hp{100}, max_hp{100}
{
    rectangleshape.setSize(size);
    rectangleshape.setTexture(texture);
    rectangleshape.setTextureRect(sf::IntRect({0,0},{static_cast<int>(size.x),static_cast<int>(size.y)}));
    rectangleshape.setScale({unit_size / 16.0f, unit_size / 16.0f});

    rectangleshape.setPosition({position.x * unit_size, position.y * unit_size});
}

entity::entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, uint8_t hp, uint8_t max_hp) : position{position}, size{size}, texture{texture}, hp{hp}, max_hp{max_hp}
{
    rectangleshape.setSize(size);
    rectangleshape.setTexture(texture);
    rectangleshape.setTextureRect(sf::IntRect({0,0},{static_cast<int>(size.x),static_cast<int>(size.y)}));
    rectangleshape.setScale({unit_size / 16.0f, unit_size / 16.0f});

    rectangleshape.setPosition({position.x * unit_size, position.y * unit_size});
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

void entity::updateRect()
{
    rectangleshape.setScale({unit_size / 16.0f, unit_size / 16.0f});
    rectangleshape.setPosition({position.x * unit_size, position.y * unit_size});        
}

sf::RectangleShape& entity::rectangle()
{
    return rectangleshape;
}

void entity::move(sf::Vector2f delta)
{
    position += delta;
}

void entity::teleport(sf::Vector2f new_position)
{
    position = new_position;
}

sf::Vector2f entity::getPosition() const
{
    return position;
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