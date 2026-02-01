#include "../include/effect.hpp"
#include "../include/entity.hpp"
#include "../include/game.hpp"

extern game dungeon_shooter_game;

effect::effect(const std::string& name, int duration, int potency, sf::Texture* icon, std::function<void(entity&)> apply_effect) : name(name), duration(duration), potency(potency), icon(icon), apply_effect(apply_effect)
{}

void effect::apply(entity& target) const
{
    apply_effect(target);
}


std::string effect::getName() const
{
    return name;
}


int effect::getDuration() const
{
    return duration;
}

void effect::decreaseDuration(int amount)
{
    duration -= amount;
}

int effect::getPotency() const
{
    return potency;
}

sf::Texture* effect::getIcon() const
{
    return icon;
}

effect effect::Poison(int duration, int potency)
{
    return 
    effect("Poison", duration, potency, &dungeon_shooter_game.poison_texture, [potency](entity& target)
        {
            target.decreaseHP(potency);
        }
    );
}

effect effect::Regeneration(int duration, int potency)
{
    return 
    effect("Regeneration", duration, potency, nullptr, [potency](entity& target)
        {
            target.increaseHP(potency);
        }
    );
}