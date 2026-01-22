#include "../include/game.hpp"
#include "../include/inventory.hpp"

// PLAYER

void player::operator=(const player& other)
{
    entity::operator=(other);
}

void game::takeScreenshoot()
{
    sf::Vector2u size = window.getSize();
    sf::Texture texture(size);

    texture.update(window);

    sf::Image screenshoot = texture.copyToImage();

    if(!screenshoot.saveToFile(std::to_string(time(nullptr)) + ".png")) return;
}

bool player::canRun()
{
    return stamina > 0.0f;
}

void player::increaseStamina(float delta)
{
    if((stamina + delta) <= stamina_limit)
    {
        stamina += delta;
    }
    else stamina = stamina_limit;
}

void player::decreaseStamina(float delta)
{
    if((stamina - delta) >= 0)
    {
        stamina -= delta;
    }
    else stamina = 0.0f;
}

float player::Stamina()
{
    return stamina;
}

inventory& player::getInventory()
{
    return inventory_;
}