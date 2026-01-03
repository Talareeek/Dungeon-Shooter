#include "..\include\headers.hpp"

#include "..\include\block.hpp"

extern unsigned int unit_size;
extern bool random_tick;


extern std::vector<sf::Texture*> game_textures;

block::block(sf::Vector2f position, sf::Vector2f size, sf::Texture* texture, game* game_instance, std::function<void(block*, game*)> on_update) : position{position}, size{size}, texture{texture}, on_update{on_update}, game_instance{game_instance}
{
    rectangleshape.setSize(size);
    rectangleshape.setTexture(texture);
    rectangleshape.setTextureRect(sf::IntRect({0,0},{static_cast<int>(size.x),static_cast<int>(size.y)}));
    rectangleshape.setScale({unit_size / 16.0f, unit_size / 16.0f});

    rectangleshape.setPosition({position.x * unit_size, position.y * unit_size});
}

block::block(block&& other) noexcept
{
    position = other.position;
    size = other.size;
    texture = other.texture;
    rectangleshape = other.rectangleshape;
    on_update = other.on_update;
}

block::block() : block(block::Air({0,0}))
{
    
}

void block::operator=(const block& other)
{
    position = other.position;
    size = other.size;
    texture = other.texture;
    rectangleshape = other.rectangleshape;
    on_update = other.on_update;
}

void block::updateRect()
{
    position = {static_cast<float>(static_cast<int>(position.x)), static_cast<float>(static_cast<int>(position.y))}; //snap to grid
    rectangleshape.setScale({unit_size / 16.0f, unit_size / 16.0f});
    rectangleshape.setPosition({position.x * unit_size, position.y * unit_size});        
}

sf::RectangleShape& block::rectangle()
{
    return rectangleshape;
}

void block::update()
{
    //on_update(this, game_instance);
    updateRect();
}

void block::move(sf::Vector2f delta)
{
    position += delta;
}

void block::teleport(sf::Vector2f new_position)
{
    position = new_position;
}

sf::Vector2f block::getPosition() const
{
    return position;
}

bool block::isAir() const
{
    return texture == nullptr;
}

block::operator bool() const
{
    return !isAir();
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