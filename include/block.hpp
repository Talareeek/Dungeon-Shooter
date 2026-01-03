#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "headers.hpp"

class game;

class block
{
private:

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Texture* texture = nullptr;

    sf::RectangleShape rectangleshape;

    std::function<void(block*, game*)> on_update;

    game* game_instance = nullptr;

public:

    block(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, game* game_instance = nullptr, std::function<void(block*, game*)> on_update = [](block*, game*){});

    block(block&& other) noexcept;

    block();

    void operator=(const block& other);

    void updateRect();

    sf::RectangleShape& rectangle();

    void update();

    void move(sf::Vector2f delta);

    void teleport(sf::Vector2f new_position);

    sf::Vector2f getPosition() const;

    bool isAir() const;

    explicit operator bool() const;

    static block Air(sf::Vector2f position);

    static block Wall(sf::Vector2f position);

    static block Floor(sf::Vector2f position);

    static block Spawner(sf::Vector2f position);

};

#endif // BLOCK_HPP