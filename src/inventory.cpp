// DUNGEON SHOOTER
// inventory.hpp
// Talareeek
// https://github.com/Talareeek/Dungeon-Shooter

#include "../include/headers.hpp"

#include "../include/inventory.hpp"

extern sf::Texture slot_texture;

extern sf::Font main_font;

extern unsigned int unit_size;

inventory::inventory()
{

}

item inventory::pickUpWithLeftover(item& to_pickup)
{
    size_t closest_x = 10, closest_y = 4;

    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(slots[y][x].getName() == "" && closest_x == 10 && closest_y == 4)
            {
                closest_x = x;
                closest_y = y;
            }

            if(slots[y][x].getName() == to_pickup.getName())
            {
                to_pickup = slots[y][x].increaseAmountWithLeftover(to_pickup.getAmount());
                if(to_pickup.getAmount() == 0) break;
            }
        }
    }

    if(closest_x != 10 && closest_y != 4)
    {
        slots[closest_y][closest_x] = to_pickup;
        to_pickup.setAmount(0);
        return item(to_pickup);
    }

    return item(to_pickup);
}

size_t inventory::getAmountOf(std::string item_name)
{
    size_t amount = 0;

    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(slots[y][x].getName() == item_name) amount += slots[y][x].getAmount();
        }
    }

    return amount;
}

bool inventory::decreaseAmountOf(std::string item_name, size_t by)
{
    size_t remaining = by;

    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(slots[y][x].getName() == item_name) remaining = slots[y][x].decreaseAmountWithLeftover(remaining);
        }
    }

    return !static_cast<bool>(remaining);
}

void inventory::draw(sf::RenderWindow& window)
{
    int start_x = window.getSize().x / 2 - unit_size * 5;
    int start_y = window.getSize().y / 2 - unit_size * 2;

    sf::RectangleShape slot({1.0f, 1.0f});
    slot.setScale({static_cast<float>(unit_size), static_cast<float>(unit_size)});

    slot.setTexture(&slot_texture);

    slot.setTextureRect({{0, 0}, {16, 16}});

    sf::Text text(main_font, "0", unit_size / 3);
    text.setFillColor(sf::Color::White);


    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            slot.setPosition({static_cast<float>(start_x + unit_size * x), static_cast<float>(start_y + unit_size * y)});
            window.draw(slot);
            
            if(slots[y][x].getName() != "" && slots[y][x].getAmount() != 0)
            {
                slot.setTexture(slots[y][x].getTexture());
                window.draw(slot);
                slot.setTexture(&slot_texture);

                text.setPosition({static_cast<float>(start_x + unit_size * (x + 1/16)), static_cast<float>(start_y + unit_size * (y - 1/16))});
                text.setString(std::to_string(slots[y][x].getAmount()));
                window.draw(text);
            }
        }
    }
}