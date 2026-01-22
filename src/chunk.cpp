#include "../include/chunk.hpp"
#include "../include/item_object.hpp"

extern std::vector<sf::Texture*> game_textures;

chunk::chunk() : chunk({0, 0})
{
    generated = up_open = down_open = left_open = right_open = false;
}

chunk::chunk(sf::Vector2f position) : position{position}
{
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            blocks[y][x] = block({position.x + x, position.y + y}, {0, 0}, nullptr);
        }
    }

    generated = up_open = down_open = left_open = right_open = false;
}

void chunk::setPosition(sf::Vector2f position)
{
    this->position = position;

    for(int y = 0; y < 8; y++)
        for(int x = 0; x < 8; x++)
            blocks[y][x].teleport({position.x + x, position.y + y});
}


void chunk::generate(bool up, bool down, bool left, bool right)
{
    if(generated) throw std::runtime_error("Generating the same chunk second time");

    up_open = up;
    down_open = down;
    left_open = left;
    right_open = right;


    for (int x = 0; x < 8; x++)
    {
        blocks[7][x] = (up_open && x != 0 && x != 7) ? block({position.x + x, position.y + 7}, {1, 1}, nullptr) : block({position.x + x, position.y + 7}, {1, 1}, game_textures[1]);
    }


    for (int x = 0; x < 8; x++)
    {
        blocks[0][x] = (down_open && x != 0 && x != 7) ? block({position.x + x, position.y + 0}, {1, 1}, nullptr) : block({position.x + x, position.y + 0}, {1, 1}, game_textures[1]);
    }


    for (int y = 0; y < 8; y++)
    {
        blocks[y][0] = (left_open && y != 0 && y != 7) ? block({position.x + 0, position.y + y}, {1, 1}, nullptr) : block({position.x + 0, position.y + y}, {1, 1}, game_textures[1]);
    }

    for (int y = 0; y < 8; y++)
    {
        blocks[y][7] = (right_open && y != 0 && y != 7) ? block({position.x + 7, position.y + y}, {1, 1}, nullptr) : block({position.x + 7, position.y + y}, {1, 1}, game_textures[1]);
    }

    generated = true;
}

bool chunk::isUpOpen()
{
    return up_open;
}

bool chunk::isDownOpen()
{
    return down_open;
}

bool chunk::isLeftOpen()
{
    return left_open;
}

bool chunk::isRightOpen()
{
    return right_open;
}

bool chunk::isGenerated()
{
    return generated;
}

bool chunk::collides(object& object_)
{
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if(blocks[y][x].collides(object_) && !(blocks[y][x].isNULL()))
            {
                return true;
            }
        }
    }
    return false;
}

void chunk::update()
{
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            blocks[y][x].update();
        }
    }
}

void chunk::draw(sf::RenderWindow& window)
{
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if(!(blocks[y][x] .isNULL()))
            {
                window.draw(blocks[y][x].rectangle());
            }
        }
    }
}