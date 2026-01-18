#include "../include/game.hpp"

// PLAYER

void player::operator=(const player& other)
{
    entity::operator=(other);
    current_weapon = other.current_weapon;
}

void player::changeWeapon(WEAPON new_weapon)
{
    current_weapon = new_weapon;
}

void player::changeWeapon(int delta)
{
    if(delta > 0)
    {
        // Scroll up - switch to next weapon
        switch(current_weapon)
        {
            case WEAPON::RIFLE:
                current_weapon = WEAPON::SHOTGUN;
                break;
            case WEAPON::SHOTGUN:
                current_weapon = WEAPON::SNIPER;
                break;
            case WEAPON::SNIPER:
                current_weapon = WEAPON::RIFLE;
                break;
        }
    }
    else if(delta < 0)
    {
        // Scroll down - switch to previous weapon
        switch(current_weapon)
        {
            case WEAPON::RIFLE:
                current_weapon = WEAPON::SNIPER;
                break;
            case WEAPON::SHOTGUN:
                current_weapon = WEAPON::RIFLE;
                break;
            case WEAPON::SNIPER:
                current_weapon = WEAPON::SHOTGUN;
                break;
        }
    }
}

player::WEAPON player::getCurrentWeapon() const
{
    return current_weapon;
}

void game::takeScreenshoot()
{
    sf::Vector2u size = window.getSize();
    sf::Texture texture(size);

    texture.update(window);

    sf::Image screenshoot = texture.copyToImage();

    if(!screenshoot.saveToFile(std::to_string(time(nullptr)) + ".png")) return;
}