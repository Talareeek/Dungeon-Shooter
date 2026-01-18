#include "../include/headers.hpp"
#include "../include/item.hpp"

item::item()
{
    
}


item::item(std::string name, size_t max_amount, size_t amount, sf::Texture* texture) : name{name}, max_amount{max_amount}, amount{amount}, texture{texture}
{

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