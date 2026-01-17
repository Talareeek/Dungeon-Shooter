#ifndef ITEM_OBJECT_HPP
#define ITEM_OBJECT_HPP

#include "item.hpp"
#include "object.hpp"

class item_object : public item, public object
{
private:

public:

    item asItem();

    object asObject();
};

#endif // ITEM_OBJECT_HPP