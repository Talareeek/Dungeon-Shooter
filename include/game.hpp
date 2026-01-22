#ifndef GAME_HPP
#define GAME_HPP

#include "headers.hpp"

#include "entity.hpp"
#include "map.hpp"
#include "block.hpp"
#include "chunk.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include "item_object.hpp"

class game
{
private:
    //WINDOW
    sf::RenderWindow window;

    //TEXTURES

    //SPRITES
    std::optional<sf::Sprite> floor;
    std::optional<sf::Sprite> crosshair;
    std::optional<sf::Sprite> vignette;

    //SOUNDS
    sf::SoundBuffer shoot_sound_buffer;
    std::optional<sf::Sound> shoot_sound;

    //OTHER  

    player main_player;

    bool debug_mode = false;

    map* main_map;

    std::vector<bullet> bullets;

    item_object test_item;

    //DEBUG MENU
    std::chrono::steady_clock::time_point last_debug_toggle;
    std::chrono::milliseconds debug_toggle_cooldown{100};

    //RANDOM TICK
    std::random_device rd;
    std::mt19937 rnd{rd()};
    std::bernoulli_distribution random_tick_dist{0.001666666667}; // ~ 1/600

    block get_block_from_ip(unsigned int ip);

    void takeScreenshoot();

    std::chrono::steady_clock::time_point last_screenshoot;
    std::chrono::milliseconds screenshoot_cooldown{500};

    void handleEvents();

    void render();

    void update();

public:

    game();

    

    void run();

    friend class block;
    friend class map;
};

#endif // GAME_HPP