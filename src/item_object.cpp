#include "../include/item_object.hpp"

item_object::item_object()
{

}

item_object::item_object(item&& other_item, object&& other_object) : item(std::move(other_item)), object(std::move(other_object))
{

}

item item_object::asItem()
{
    return item(*this);
}

object item_object::asObject()
{
    return object(*this);
}