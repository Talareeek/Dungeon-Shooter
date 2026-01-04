#include "..\include\headers.hpp"

#include "..\include\block.hpp"
#include "..\include\entity.hpp"

extern unsigned int unit_size;
extern bool random_tick;


extern std::vector<sf::Texture*> game_textures;

void block::update()
{
    position = {static_cast<float>(static_cast<int>(position.x)), static_cast<float>(static_cast<int>(position.y))};
    object::update();
}

block block::Air(sf::Vector2f position)
{
    return block(position, {16, 16}, nullptr);
}

block block::Wall(sf::Vector2f position)
{
    return block(position, {16, 16}, game_textures[1]);
}

block block::Floor(sf::Vector2f position)
{
    return block(position, {16, 16}, game_textures[0]);
}

block block::Spawner(sf::Vector2f position)
{
    return block(position, {16, 16}, game_textures[2]);
}