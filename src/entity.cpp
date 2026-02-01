#include "..\include\headers.hpp"
#include "..\include\entity.hpp"
#include "..\include\game.hpp"

extern unsigned int unit_size;
extern bool random_tick;

extern game dungeon_shooter_game;


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

void entity::update()
{
    object::update();

    for(auto it = active_effects.begin(); it != active_effects.end(); )
    {
        it->apply(*this);
        it->decreaseDuration();
        if(it->getDuration() <= 0)
        {
            it = active_effects.erase(it);
        }
        else
        {
            ++it;
        }
    }
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

uint8_t entity::getMaxHP() const
{
    return max_hp;
}

void entity::applyEffect(const effect& new_effect)
{
    active_effects.push_back(new_effect);
}

const std::vector<effect>& entity::getActiveEffects() const
{
    return active_effects;
}

void entity::drawActiveEffects(sf::RenderWindow& window)
{
    int start_x = 10;
    int start_y = 10;

    int index = 0;

    for(auto& a : active_effects)
    {
        sf::RectangleShape background;
        background.setSize({unit_size, unit_size});
        background.setTexture(&dungeon_shooter_game.slot_texture);
        background.setPosition({static_cast<float>(start_x), static_cast<float>(start_y) + unit_size * index});

        window.draw(background);

        if(a.getIcon())
        {
            sf::RectangleShape icon_shape;
            icon_shape.setSize({unit_size, unit_size});
            icon_shape.setTexture(a.getIcon());
            icon_shape.setPosition({static_cast<float>(start_x), static_cast<float>(start_y) + unit_size * index});
            window.draw(icon_shape);
        }
        index++;
    }
}