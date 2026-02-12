// DUNGEON SHOOTER
// inventory.hpp
// Talareeek
// https://github.com/Talareeek/Dungeon-Shooter

#include "../include/headers.hpp"

#include "../include/inventory.hpp"

#include "../include/game.hpp"

#include "../include/target.hpp"


extern unsigned int unit_size;

extern game dungeon_shooter_game;

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

    slot.setTexture(&dungeon_shooter_game.slot_texture);

    slot.setTextureRect({{0, 0}, {16, 16}});

    sf::Text text(dungeon_shooter_game.main_font, "0", unit_size / 3);
    text.setFillColor(sf::Color::White);


    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            slot.setTexture(&dungeon_shooter_game.slot_texture);

            slot.setPosition({static_cast<float>(start_x + unit_size * x), static_cast<float>(start_y + unit_size * y)});
            window.draw(slot);

            if(x == selected_x && y == selected_y)
            {
                slot.setTexture(&dungeon_shooter_game.selected_slot_texture);
                window.draw(slot);
            }
            
            if(slots[y][x].getName() != "" && slots[y][x].getAmount() != 0)
            {
                slot.setTexture(slots[y][x].getTexture());
                window.draw(slot);
                

                text.setPosition({static_cast<float>(start_x + unit_size * (x + 1/16)), static_cast<float>(start_y + unit_size * (y - 1/16))});
                text.setString(std::to_string(slots[y][x].getAmount()));
                window.draw(text);
            }
        }
    }
}

void inventory::changeSelectedX(int delta)
{
    selected_x = (selected_x + delta + 10) % 10;
}

void inventory::changeSelectedY(int delta)
{
    selected_y = (selected_y + delta + 4) % 4;
}

int inventory::getSelectedX()
{
    return selected_x;
}

int inventory::getSelectedY()
{
    return selected_y;
}

void inventory::attackTriggered(target& target_)
{
    slots[selected_y][selected_x].attackTriggered(target_);
}

void inventory::useTriggered(target& target_)
{
    slots[selected_y][selected_x].useTriggered(target_);
}

item& inventory::getSelected()
{
    return slots[selected_y][selected_x];
}