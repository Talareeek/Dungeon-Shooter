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