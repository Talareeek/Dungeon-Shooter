#include "../include/item_object.hpp"

item item_object::asItem()
{
    return item(*this);
}

object item_object::asObject()
{
    return object(*this);
}