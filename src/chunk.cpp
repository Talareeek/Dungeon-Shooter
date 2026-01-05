#include "../include/chunk.hpp"

chunk::chunk(sf::Vector2f position) : position{position}
{
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            blocks[y][x] = block::Air({position.x + x, position.y + y});
        }
    }
}

void chunk::generate(bool up, bool down, bool left, bool right)
{
    if(generated) throw std::runtime_error("Generating the same chunk second time");

    up_open = up;
    down_open = down;
    left_open = left;
    right_open = right;

    //UP
    if(up_open)
    {
        
    }
}