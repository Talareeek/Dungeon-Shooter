#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include "object.hpp"

class inventory
{
private:

    item slots[4][10];

    int selected_x = 0;
    int selected_y = 0;

public:

    inventory();

    item pickUpWithLeftover(item& to_pickup);

    size_t getAmountOf(std::string item_name);

    bool decreaseAmountOf(std::string item_name, size_t by);

    void draw(sf::RenderWindow& window);

    void changeSelectedX(int delta);

    void changeSelectedY(int delta);

    int getSelectedX();

    int getSelectedY();

    void attackTriggered(target& target_);

    void useTriggered(target& target_);

    item& getSelected();
};

#endif // INVENTORY_HPP