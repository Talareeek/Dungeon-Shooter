#ifndef GAME_HPP
#define GAME_HPP

#include "headers.hpp"

#include "entity.hpp"
#include "map.hpp"
#include "block.hpp"

class game
{
private:

    struct bullet
    {
        float scale;
        sf::Texture* texture;

        sf::Vector2f position;
        uint8_t damage;

        sf::RectangleShape rect;

        float speed;

        float direction_angle;

        bullet(sf::Vector2f start_pos, sf::Texture* texture, float scale, uint8_t damage_value,  float direction_angle, float speed);

        void update(float delta_time);
    };

    //PLAYER
    class player : public entity
    {
    public:

        enum class WEAPON
        {
            RIFLE,
            SHOTGUN,
            SNIPER
        };

    private:

        WEAPON current_weapon = WEAPON::RIFLE;

    public:        

        using entity::entity;

        void operator=(const player& other);

        void changeWeapon(WEAPON new_weapon);

        void changeWeapon(int delta);

        WEAPON getCurrentWeapon() const;
    };


    //WINDOW
    sf::RenderWindow window;

    //TEXTURES
    sf::Texture lobby_background_texture;
    sf::Texture player_texture;
    sf::Texture bullet_texture;
    sf::Texture floor_texture;
    sf::Texture spawner_texture;
    sf::Texture crosshair_texture;
    sf::Texture wall_texture;
    sf::Texture air_texture;

    //FONTS
    sf::Font main_font;

    //SPRITES
    std::optional<sf::Sprite> floor;
    std::optional<sf::Sprite> crosshair;

    //SOUNDS
    sf::SoundBuffer shoot_sound_buffer;
    std::optional<sf::Sound> shoot_sound;

    //OTHER  

    player main_player;

    bool debug_mode = false;

    map* main_map;

    std::vector<bullet> bullets;

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