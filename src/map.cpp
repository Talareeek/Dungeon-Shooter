#include "..\include\headers.hpp"

#include "..\include\map.hpp"
#include "..\include\game.hpp"
#include "..\include\block.hpp"

extern std::vector<sf::Texture*> game_textures;

void map::chunk::generate(bool up_open, bool down_open, bool left_open, bool right_open)
{
    if(isGenerated()) return;

    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            blocks[y][x] = block::Air({static_cast<float>(position.x + x), static_cast<float>(position.y + y)});
        }
    }

    this->up_open = up_open;
    this->down_open = down_open;
    this->left_open = left_open;
    this->right_open = right_open;

    float x = position.x;
    float y = position.y;

    

    // UP WALL
    for(size_t i = 0; i < 8; i++)
    {
        if(!up_open)
        {
            blocks[0][i] = block::Wall(sf::Vector2f(x + i, y));
        }
        else
        {
            if(i == 0 || i == 7)
            {
                blocks[0][i] = block::Wall(sf::Vector2f(x + i, y));
            }
        }
    }

    // DOWN WALL
    for(size_t i = 0; i < 8; i++)
    {
        if(!down_open)
        {
            blocks[7][i] = block::Wall(sf::Vector2f(x + i, y + 7));
        }
        else
        {
            if(i == 0 || i == 7)
            {
                blocks[7][i] = block::Wall(sf::Vector2f(x + i, y + 7));
            }
        }
    }

    // LEFT WALL
    for(size_t i = 0; i < 8; i++)
    {
        if(!left_open)
        {
            blocks[i][0] = block::Wall(sf::Vector2f(x, y + i));
        }
        else
        {
            if(i == 0 || i == 7)
            {
                blocks[i][0] = block::Wall(sf::Vector2f(x, y + i));
            }
        }
    }

    // RIGHT WALL
    for(size_t i = 0; i < 8; i++)
    {
        if(!right_open)
        {
            blocks[i][7] = block::Wall(sf::Vector2f(x + 7, y + i));
        }
        else
        {
            if(i == 0 || i == 7)
            {
                blocks[i][7] = block::Wall(sf::Vector2f(x + 7, y + i));
            }
        }
    }

    generated = true;
}

bool map::chunk::isGenerated() const
{
    return generated;
}

void map::chunk::draw(sf::RenderWindow& window)
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(blocks[y][x])
                window.draw(blocks[y][x].rectangle());
        }
    }
}

void map::chunk::update()
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            blocks[y][x].update();
        }
    }
}

bool map::chunk::isUpOpen() const
{
    return up_open;
}

bool map::chunk::isDownOpen() const
{
    return down_open;
}

bool map::chunk::isLeftOpen() const
{
    return left_open;
}

bool map::chunk::isRightOpen() const
{
    return right_open;
}

sf::Vector2f map::chunk::getPosition() const
{
    return position;
}

void map::chunk::setPosition(sf::Vector2f new_position)
{
    position = new_position;
}

void map::chunk::fillWith(block block_)
{
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            blocks[y][x] = block_;
            blocks[y][x].teleport({position.x + x, position.y + y});
            blocks[y][x].update();
        }
    }
}

bool map::chunk::collidesWith(object& object_)
{

    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(blocks[y][x].collides(object_)) return true;
        }
    }
    return false;
}

map::map()
{
    for(int x = 0; x < 128; x++)
    {
        for(int y = 0; y < 128; y++)
        {
            chunks[y][x].setPosition(sf::Vector2f{static_cast<float>((x - 64) * 8), static_cast<float>((y - 64) * 8)});
        }
    }
}

void map::generate()
{
    std::stack<std::pair<size_t, size_t>> s;
    s.push({64, 64});

    chunks[64][64].generate(true, true, true, true);

    while (!s.empty())
    {
        auto [x, y] = s.top();
        s.pop();

        if (chunks[y][x].isUpOpen() && y > 0 && !chunks[y - 1][x].isGenerated())
        {
            chunks[y - 1][x].generate(rand()%2, true, rand()%2, rand()%2);
            s.push({x, y - 1});
        }
        if (chunks[y][x].isDownOpen() && y < 127 && !chunks[y + 1][x].isGenerated())
        {
            chunks[y + 1][x].generate(true, rand()%2, rand()%2, rand()%2);
            s.push({x, y + 1});
        }
        if (chunks[y][x].isLeftOpen() && x > 0 && !chunks[y][x - 1].isGenerated())
        {
            chunks[y][x - 1].generate(rand()%2, rand()%2, rand()%2, true);
            s.push({x - 1, y});
        }
        if (chunks[y][x].isRightOpen() && x < 127 && !chunks[y][x + 1].isGenerated())
        {
            chunks[y][x + 1].generate(rand()%2, rand()%2, true, rand()%2);
            s.push({x + 1, y});
        }
    }

    for(int x = 0; x < 128; x++)
    {
        for(int y = 0; y < 128; y++)
        {
            if(!chunks[y][x].isGenerated())
            {
                chunks[y][x].fillWith(block::Wall({0, 0}));
            }
        }
    }
}


void map::draw(sf::RenderWindow& window, sf::Vector2f position)
{
    int player_chunk_x = static_cast<int>(position.x / 8.0f) + 64;
    int player_chunk_y = static_cast<int>(position.y / 8.0f) + 64;

    int minX = std::max(0, player_chunk_x - 3);
    int maxX = std::min(127, player_chunk_x + 3);
    int minY = std::max(0, player_chunk_y - 3);
    int maxY = std::min(127, player_chunk_y + 3);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            chunks[y][x].draw(window);
        }
    }
}

bool map::collidesWith(object& object_)
{
    int player_chunk_x = static_cast<int>(object_.rectangle().getPosition().x / 8.0f) + 64;
    int player_chunk_y = static_cast<int>(object_.rectangle().getPosition().y / 8.0f) + 64;


    int minX = std::max(0, player_chunk_x - 1);
    int maxX = std::min(127, player_chunk_x + 1);

    int minY = std::max(0, player_chunk_y - 1);
    int maxY = std::min(127, player_chunk_y + 1);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if(chunks[y][x].collidesWith(object_))
                return true;
        }
    }


    return false;
}

#include <fstream>

void map::exportToFile(std::string& destination)
{
    std::ofstream stream(destination);

    if (!stream.is_open())
        return;

    // iterujemy PO BLOKACH, nie po chunkach
    for (int globalY = 0; globalY < 128 * 8; globalY++)
    {
        for (int globalX = 0; globalX < 128 * 8; globalX++)
        {
            int chunkX = globalX / 8;
            int chunkY = globalY / 8;

            int localX = globalX % 8;
            int localY = globalY % 8;

            const block& b = chunks[chunkY][chunkX].blocks[localY][localX];

            if (b)      // operator bool → ma teksturę → Wall
                stream << '#';
            else        // Air
                stream << '.';
        }
        stream << '\n';
    }

    stream.close();
}