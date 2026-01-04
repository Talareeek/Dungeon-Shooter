#ifndef MAP_HPP
#define MAP_HPP

#include "headers.hpp"
#include "block.hpp"
#include "object.hpp"

class map
{
public:

    class chunk
    {
    private:

        sf::Vector2f position;

        block blocks[8][8];        

        bool up_open = false;
        bool down_open = false;
        bool left_open = false;
        bool right_open = false;

        bool generated = false;

    public:

        chunk(const sf::Vector2f& position = {0, 0}) : position(position) {};

        void generate(bool up_open, bool down_open, bool left_open, bool right_open);

        void draw(sf::RenderWindow& window);
        
        void update();

        bool isGenerated() const;

        bool isUpOpen() const;

        bool isDownOpen() const;

        bool isLeftOpen() const;

        bool isRightOpen() const;

        sf::Vector2f getPosition() const;

        void setPosition(sf::Vector2f new_position);

        void fillWith(block block_);

        bool collidesWith(object& object_);

        friend map;
    };

    

private:

    chunk chunks[128][128];

public:

    map();

    void generate();

    void draw(sf::RenderWindow& window, sf::Vector2f position);

    bool collidesWith(object& object_);

    void exportToFile(std::string& destination);
};

#endif // MAP_HPP