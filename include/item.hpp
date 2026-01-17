#ifndef ITEM_HPP
#define ITEM_HPP

#include "headers.hpp"

class item
{
private:

    std::string name;
    size_t max_amount;
    size_t amount;
    
    sf::Texture* texture;

public:

    item(std::string name, size_t max_amount, size_t amount, sf::Texture* texture);

    std::string getName();

    size_t getMaxAmount();

    size_t getAmount();

    sf::Texture* getTexture();

    void changeAmount(long long delta);

    void setAmount(size_t amount);
};

#endif // ITEM_HPP