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

    item_object pistol_item;
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

    std::vector<object*> toUpdate;

public:

    sf::Texture lobby_background_texture;
    sf::Texture player_texture;
    sf::Texture bullet_texture;
    sf::Texture floor_texture;
    sf::Texture spawner_texture;
    sf::Texture crosshair_texture;
    sf::Texture wall_texture;
    sf::Texture air_texture;
    sf::Texture vignette_texture;
    sf::Texture pistol_texture;
    sf::Texture slot_texture;
    sf::Texture selected_slot_texture;
    sf::Texture poison_texture;

    game();

    

    void run();

    player& getPlayer();

    std::vector<bullet>& getBullets();

    friend class block;
    friend class map;
};

#endif // GAME_HPP