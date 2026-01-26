#include "../include/headers.hpp"
#include "../include/item.hpp"

item::item()
{
    
}


item::item(std::string name, size_t max_amount, size_t amount, sf::Texture* texture, std::function <void(object&)> onAttack, std::function <void(object&)> onUse) : name{name}, max_amount{max_amount}, amount{amount}, texture{texture}, onAttack{onAttack}, onUse{onUse}
{

}

item& item::operator=(const item& other)
{
    this->name = other.name;
    this->max_amount = other.max_amount;
    this->amount = other.amount;
    this->texture = other.texture;

    return *this;
}


std::string item::getName()
{
    return name;
}


size_t item::getMaxAmount()
{
    return max_amount;
}


size_t item::getAmount()
{
    return amount;
}


sf::Texture* item::getTexture()
{
    return texture;
}

item item::increaseAmountWithLeftover(size_t delta)
{
    size_t new_amount = amount + delta;

    if(new_amount <= max_amount)
    {
        amount = new_amount;
        return item(this->name, this->max_amount, 0, this->texture);
    }
    else
    {
        amount = max_amount;
        return item(this->name, this->max_amount, new_amount - max_amount, this->texture);
    }
}

size_t item::decreaseAmountWithLeftover(size_t delta)
{
    int new_amount = amount - delta;

    if(new_amount >= 0)
    {
        amount = new_amount;
        return 0;
    }
    else
    {
        amount = 0;
        return -(new_amount);
    }
}

void item::changeAmount(long long delta)
{
    size_t new_amount = amount + delta;

    if(new_amount <= max_amount)
    {
        amount = new_amount;
    }
}

void item::setAmount(size_t amount)
{
    if(amount <= max_amount)
    {
        this->amount = amount;
    }
}

void item::attackTriggered(object& target)
{
    onAttack(target);
}

void item::useTriggered(object& target)
{
    onUse(target);
}