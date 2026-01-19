#include "..\include\headers.hpp"

#include "..\include\game.hpp"
#include "..\include\entity.hpp"
#include "..\include\block.hpp"
#include "..\include\map.hpp"

unsigned int unit_size;
bool random_tick = false;
extern bool dev_mode;

std::vector<sf::Texture*> game_textures;

game::game()
{
    //WINDOW SETUP
    window.create(sf::VideoMode::getDesktopMode(), "Dungeon Shooter", sf::State::Fullscreen);

    //UNIT SIZE
    unit_size = window.getSize().y / 9;

    // LOADING RESOURCES
    if(!lobby_background_texture.loadFromFile("resources/textures/lobby_background.png")) throw std::runtime_error("Cannot load lobby background texture");
    if(!floor_texture.loadFromFile("resources/textures/floor.png")) throw std::runtime_error("Cannot load floor texture");
    if(!bullet_texture.loadFromFile("resources/textures/bullet.png")) throw std::runtime_error("Cannot load bullet texture");
    if(!player_texture.loadFromFile("resources/textures/player.png")) throw std::runtime_error("Cannot load player texture");
    if(!main_font.openFromFile("resources/fonts/PressStart2P-Regular.ttf")) throw std::runtime_error("Cannot load main font");
    if(!spawner_texture.loadFromFile("resources/textures/spawner.png")) throw std::runtime_error("Cannot load spawner texture");
    if(!shoot_sound_buffer.loadFromFile("resources/sounds/shoot.mp3")) throw std::runtime_error("Cannot load shoot sound");
    if(!crosshair_texture.loadFromFile("resources/textures/crosshair.png")) throw std::runtime_error("Cannot load crosshair texture");
    if(!wall_texture.loadFromFile("resources/textures/wall.png")) throw std::runtime_error("Cannot load wall texture");
    if(!vignette_texture.loadFromFile("resources/textures/vignette.png")) throw std::runtime_error("Cannot load vignette texture");

    floor_texture.setRepeated(true);
    crosshair_texture.setSmooth(false);

    game_textures = {&floor_texture, &wall_texture, &spawner_texture};

    // SETUP FLOOR SPRITE
    floor.emplace(floor_texture);    
    floor->setTextureRect(sf::IntRect({0, 0}, {16 * 1024, 16 * 1024}));
    floor->setScale(sf::Vector2f(static_cast<float>(unit_size / 16.0f), static_cast<float>(unit_size / 16.0f)));
    floor->setOrigin(sf::Vector2f(16 * 1024 / 2.0f, 16 * 1024 / 2.0f));
    floor->setPosition(sf::Vector2f(0.0f, 0.0f));
    

    //LEGACY RANDOM SETUP
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // MAP GENERATION
    main_map = new map();
    main_map->generate();



    //PLAYER SETUP
    main_player = player(sf::Vector2f(4, 4), sf::Vector2f(1, 1), &player_texture, 100, 100);

    // TEXTURES CONFIGURATION
    


    // SPRITES SETUP
    crosshair.emplace(crosshair_texture);
    crosshair->setScale(sf::Vector2f(unit_size / 16.0f, unit_size / 16.0f));
    crosshair->setOrigin(sf::Vector2f(crosshair_texture.getSize().x / 2.0f, crosshair_texture.getSize().y / 2.0f));

    vignette.emplace(vignette_texture);
    vignette->setScale({window.getSize().y / static_cast<float>(vignette_texture.getSize().y), window.getSize().y / static_cast<float>(vignette_texture.getSize().y)});
    vignette->setOrigin({vignette_texture.getSize().x / 2.0f, vignette_texture.getSize().y / 2.0f});
    vignette->setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});

    // SETUP SHOOT SOUND
    shoot_sound.emplace(shoot_sound_buffer);
    
    // Load and configure player texture (use 16x16 tile)
    player_texture.setSmooth(false); // keep pixel-art crisp

    

    window.setMouseCursorVisible(false);
}

void game::handleEvents()
{
    while(auto event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if(event->is<sf::Event::MouseWheelScrolled>())
        {
            auto wheel_event = event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = wheel_event->delta;
            main_player.changeWeapon(static_cast<int>(delta));
        }
        if(event->is<sf::Event::MouseButtonPressed>())
        {
            auto mouse_event = event->getIf<sf::Event::MouseButtonPressed>();
            if(mouse_event->button == sf::Mouse::Button::Left)
            {
                shoot_sound->play();

                // Calculate direction angle from player to mouse position
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                sf::Vector2f world_mouse_pos = window.mapPixelToCoords(mouse_pos);

                float delta_x = world_mouse_pos.x - (main_player.getPosition().x * unit_size);
                float delta_y = world_mouse_pos.y - (main_player.getPosition().y * unit_size);

                float angle = std::atan2(delta_y, delta_x);

                // Create a new bullet
                bullets.push_back
                (
                    bullet
                    (
                    main_player.getPosition(),
                    &bullet_texture,
                    10,
                    angle,
                    10.0f // speed
                    )
                );
            }
        }
    }
}

void game::render()
{
    window.clear();

    //PLAYER POV
    sf::View player_view(
    sf::Vector2f(
        (main_player.getPosition().x + 0.5f) * unit_size,
        (main_player.getPosition().y + 0.5f) * unit_size
    ),
    sf::Vector2f(window.getSize())
    );

    window.setView(player_view);
    window.draw(*floor);
    main_map->draw(window, main_player.getPosition());
    //PLAYER
    main_player.update();
    window.draw(main_player.rectangle());

    //BULLETS
    for(auto& a : bullets)
    {
        window.draw(a.rectangle());
    }

    

    //GUI

    sf::View gui_view(sf::FloatRect({0.f, 0.f}, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
    window.setView(gui_view);

    window.draw(*vignette);

    if(!debug_mode)
    {

        sf::Text health_text(main_font, std::to_string(main_player.getHP()) + " HP", static_cast<unsigned int>((window.getSize().y / 9)));
        health_text.setFillColor(sf::Color::Red);
        auto bounds = health_text.getLocalBounds();
        health_text.setPosition({10.f, 10.f});
        window.draw(health_text);
    

        //WEAPON TEXT
        std::string weapon_str;
        switch(main_player.getCurrentWeapon())
        {
            case player::WEAPON::RIFLE:
                weapon_str = "RIFLE";
                break;
            case player::WEAPON::SHOTGUN:
                weapon_str = "SHOTGUN";
                break;
            case player::WEAPON::SNIPER:
                weapon_str = "SNIPER";
                break;
        }

        sf::Text weapon_text(main_font, weapon_str, static_cast<unsigned int>(window.getSize().y / 9));
        weapon_text.setFillColor(sf::Color::White);
        weapon_text.setOrigin(sf::Vector2f(weapon_text.getLocalBounds().size.x, 0.f)); //right top origin
        weapon_text.setPosition({static_cast<float>(window.getSize().x - 10), static_cast<float>((window.getSize().y / 9) * 8)});
        window.draw(weapon_text);

        // CROSSHAIR
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        crosshair->setPosition(window.mapPixelToCoords(mouse_pos));
        window.draw(*crosshair);
    }    
    else
    {
        //DEBUG MENU

        std::string debug_string = 
        "Unit size(px per tile): " + std::to_string(unit_size) + '\n'
        + "XY: " + std::to_string(main_player.getPosition().x) + " / " + std::to_string(main_player.getPosition().y) + '\n'
        + "Bullets: " + std::to_string(bullets.size()) + '\n'
        + "Stamina: " + std::to_string(main_player.Stamina()) + '\n';

        for(auto& a : bullets)
        {
            debug_string += "Bullet at: " + std::to_string(a.getPosition().x) + ' ' + std::to_string(a.getPosition().y) + '\n';
        }

        sf::Text debug_text(main_font, debug_string, static_cast<unsigned int>(window.getSize().y / 54));

        debug_text.setFillColor(sf::Color::White);

        debug_text.setOrigin({debug_text.getLocalBounds().size.x, 0.0f});

        debug_text.setPosition({window.getSize().x - 10.0f, 10.0f});
        window.draw(debug_text);
    }

    window.display();

    window.setView(player_view);
}





// UPDATE FUNCTION
// EACH FRAME (60 in 1 second) IT UPDATES GAME LOGIC
void game::update()
{
    //RANDOM TICK
    random_tick = static_cast<bool>(random_tick_dist(rnd));

    bool running = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && main_player.canRun();

    sf::Vector2i move;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        move.y -= 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        move.y += 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        move.x -= 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        move.x += 1;
    }

    if(move.x != 0 || move.y != 0)
    {
        float speed = running ? 8.0f : 5.0f;

        float length = std::sqrt(static_cast<float>(move.x * move.x + move.y * move.y));
        sf::Vector2f normalized_move = sf::Vector2f(static_cast<float>(move.x) / length, static_cast<float>(move.y) / length);
        sf::Vector2f previous_position = main_player.getPosition();
        main_player.move(normalized_move * speed * (1.0f / 60.0f));
        if(main_map->collides(main_player)) main_player.teleport(previous_position);
    }

    if(running) main_player.decreaseStamina(1.0f/60.0f);
    else 
    {
        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)))
            main_player.increaseStamina(1.0f/60.0f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3) && std::chrono::steady_clock::now() - last_debug_toggle > debug_toggle_cooldown)       
    {
        last_debug_toggle = std::chrono::steady_clock::now();
        debug_mode = !debug_mode;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2) && std::chrono::steady_clock::now() - last_screenshoot > screenshoot_cooldown)
    {
        last_screenshoot = std::chrono::steady_clock::now();
        takeScreenshoot();
    }

    for(auto it = bullets.begin(); it != bullets.end(); )
    {   
        it->update();
        if(main_map->collides(*it))
        {
            it = bullets.erase(it);
        }
        else it++;
    }
}





// RUN FUNCTION
// IT KEEPS THE GAME RUNNING UNTIL THE WINDOW IS CLOSED
void game::run()
{
    while(window.isOpen())
    {
        handleEvents();
        update();
        render();

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); //60 FPS
    }
}