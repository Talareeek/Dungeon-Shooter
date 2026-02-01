#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "headers.hpp"

class entity;

class effect
{
private:

    std::string name;
    int duration;
    int potency;
    sf::Texture* icon;

    std::function<void(entity&)> apply_effect;

public:

    effect(const std::string& name, int duration, int potency, sf::Texture* icon, std::function<void(entity&)> apply_effect);

    void apply(entity& target) const;
    std::string getName() const;
    int getDuration() const;
    void decreaseDuration(int amount = 1);
    int getPotency() const;
    sf::Texture* getIcon() const;

    static effect Poison(int duration, int potency);
    static effect Regeneration(int duration, int potency);

};

#endif // EFFECT_HPP