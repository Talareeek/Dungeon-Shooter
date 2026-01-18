#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"

class inventory
{
private:

    item slots[4][10];

public:

    inventory();

    void pick_up();
};

#endif // INVENTORY_HPP