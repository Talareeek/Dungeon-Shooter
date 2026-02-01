//DEPRECATED

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "headers.hpp"
#include "object.hpp"
#include "effect.hpp"

class entity : public object
{
protected:

    //HP
    uint8_t hp = 0;
    uint8_t max_hp = 0;

    std::vector<effect> active_effects;

public:

    //CONSTRUCTROR
    using object::object;
    entity(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, uint8_t hp, uint8_t max_hp);

    void update() override;

    void operator=(const entity& other);

    void setHP(uint8_t new_hp);

    void increaseHP(uint8_t delta);

    void decreaseHP(uint8_t delta);

    uint8_t getHP() const;

    uint8_t getMaxHP() const;

    void applyEffect(const effect& new_effect);
    const std::vector<effect>& getActiveEffects() const;
    void drawActiveEffects(sf::RenderWindow& window);
};

#endif // ENTITY_HPP