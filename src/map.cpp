#include "..\include\headers.hpp"
#include "..\include\map.hpp"

extern std::vector<sf::Texture*> game_textures;


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
        auto [y, x] = s.top();
        s.pop();

        if (chunks[y][x].isUpOpen() && y > 0 && !chunks[y - 1][x].isGenerated())
        {
            chunks[y - 1][x].generate(rand()%2, true, rand()%2, rand()%2);
            s.push({y - 1, x});
        }
        if (chunks[y][x].isDownOpen() && y < 127 && !chunks[y + 1][x].isGenerated())
        {
            chunks[y + 1][x].generate(true, rand()%2, rand()%2, rand()%2);
            s.push({y + 1, x});
        }
        if (chunks[y][x].isLeftOpen() && x > 0 && !chunks[y][x - 1].isGenerated())
        {
            chunks[y][x - 1].generate(rand()%2, rand()%2, rand()%2, true);
            s.push({y, x - 1});
        }
        if (chunks[y][x].isRightOpen() && x < 127 && !chunks[y][x + 1].isGenerated())
        {
            chunks[y][x + 1].generate(rand()%2, rand()%2, true, rand()%2);
            s.push({y, x + 1});
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

bool map::collides(object& object_)
{
    int player_chunk_x = static_cast<int>(object_.getPosition().x / 8.0f) + 64;
    int player_chunk_y = static_cast<int>(object_.getPosition().y / 8.0f) + 64;


    int minX = std::max(0, player_chunk_x - 1);
    int maxX = std::min(127, player_chunk_x + 1);

    int minY = std::max(0, player_chunk_y - 1);
    int maxY = std::min(127, player_chunk_y + 1);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if(chunks[y][x].collides(object_))
                return true;
        }
    }


    return false;

    /*for(int x = 0; x < 128; x++)
    {
        for(int y = 0; y < 128; y++)
        {
            if(chunks[y][x].collides(object_)) return true;
        }
    }

    return false;*/
}