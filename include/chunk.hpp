#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "headers.hpp"
#include "block.hpp"

class chunk
{
private:

    block blocks[8][8];

    sf::Vector2f position;

    bool up_open;
    bool down_open;
    bool left_open;
    bool right_open;

    bool generated = false;

public:

    chunk();

    chunk(sf::Vector2f position);

    void setPosition(sf::Vector2f position);

    void generate(bool up, bool down, bool left, bool right);

    bool isUpOpen();

    bool isDownOpen();

    bool isLeftOpen();

    bool isRightOpen();

    bool isGenerated();

    bool collides(object& object_);

    void update();  
    
    void draw(sf::RenderWindow& window);
};

#endif //CHUNK HPP