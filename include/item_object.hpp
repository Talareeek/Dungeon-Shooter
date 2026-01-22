#ifndef ITEM_OBJECT_HPP
#define ITEM_OBJECT_HPP

#include "item.hpp"
#include "object.hpp"

class item_object : public item, public object
{
private:

public:

    item_object();

    item_object(item&& other_item, object&& other_object);

    using item::operator=;
    using object::operator=;

    item asItem();

    object asObject();
};

#endif // ITEM_OBJECT_HPP