#ifndef MAP_HPP
#define MAP_HPP

#include "headers.hpp"
#include "block.hpp"
#include "entity.hpp"

class map
{
public:

    class chunk
    {
    private:
        block blocks[8][8];

        sf::Vector2f position;

        bool up_open = false;
        bool down_open = false;
        bool left_open = false;
        bool right_open = false;

    public:

        chunk(const sf::Vector2f& position = {0, 0}) : position(position) {};

        void generate(bool up_open, bool down_open, bool left_open, bool right_open);

        void draw(sf::RenderWindow& window);
        
        void update();

        bool isEmpty() const;

        bool isUpOpen() const;

        bool isDownOpen() const;

        bool isLeftOpen() const;

        bool isRightOpen() const;

        sf::Vector2f getPosition() const;

        void fillWith(block block_);

        bool collidesWith(entity& entity_);

        friend class map;
    };

private:

    chunk chunks[128][128];

public:

    map();

    void generate();

    void draw(sf::RenderWindow& window, sf::Vector2f position);

    bool collidesWith(entity& entity_);
};

#endif // MAP_HPP