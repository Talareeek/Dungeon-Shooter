#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"

class inventory
{
private:

    item slots[4][10];

public:

    inventory();

    item pickUpWithLeftover(item& to_pickup);

    size_t getAmountOf(std::string item_name);

    bool decreaseAmountOf(std::string item_name, size_t by);

    void draw(sf::RenderWindow& window);
};

#endif // INVENTORY_HPP