// Dungeon Shooter
// game.cpp


//HEADERS
#include "..\include\headers.hpp"
#include "..\include\game.hpp"
#include "..\include\entity.hpp"
#include "..\include\block.hpp"
#include "..\include\map.hpp"
#include "..\include\item_object.hpp"
#include "..\include\player.hpp"
#include "..\include\effect.hpp"
#include "..\include\input.hpp"

//EXTERNS
unsigned int unit_size;
bool random_tick = false;
extern bool dev_mode;
extern game dungeon_shooter_game;

std::vector<sf::Texture*> game_textures;

game::game()
{
    //WINDOW SETUP
    window.create(sf::VideoMode::getDesktopMode(), "Dungeon Shooter", sf::State::Fullscreen);
    //==============================
    //=Dungeon Shooter             =
    //=                            =
    //=                            =
    //=                            =
    //=                            =
    //=                            =
    //=                            =
    //=                            =
    //==============================

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
    if(!pistol_texture.loadFromFile("resources/textures/pistol.png"));
    if(!slot_texture.loadFromFile("resources/textures/slot.png")) throw std::runtime_error("Cannot load slot texture");
    if(!selected_slot_texture.loadFromFile("resources/textures/selected_slot.png")) throw std::runtime_error("Cannot load sellected slot texture");
    if(!poison_texture.loadFromFile("resources/textures/poison.png")) throw std::runtime_error("Cannot load poison texture");
    if(!enemy_texture.loadFromFile("resources/textures/tux.png")) throw std::runtime_error("Cannot load enemy texture");

    // deprecated
    game_textures = {&floor_texture, &wall_texture, &spawner_texture};


    // FLOOR SETUP
    floor_texture.setRepeated(true);
    floor.emplace(floor_texture);    
    floor->setTextureRect(sf::IntRect({0, 0}, {16 * 1024, 16 * 1024}));
    floor->setScale(sf::Vector2f(static_cast<float>(unit_size / 16.0f), static_cast<float>(unit_size / 16.0f)));
    floor->setOrigin(sf::Vector2f(16 * 1024 / 2.0f, 16 * 1024 / 2.0f));
    floor->setPosition(sf::Vector2f(0.0f, 0.0f));

    // CROSSHAIR SETUP
    crosshair_texture.setSmooth(false);
    crosshair.emplace(crosshair_texture);
    crosshair->setScale(sf::Vector2f(unit_size / 16.0f, unit_size / 16.0f));
    crosshair->setOrigin(sf::Vector2f(crosshair_texture.getSize().x / 2.0f, crosshair_texture.getSize().y / 2.0f));

    // VIGNETTE SETUP
    vignette.emplace(vignette_texture);
    vignette->setScale({window.getSize().y / static_cast<float>(vignette_texture.getSize().y), window.getSize().y / static_cast<float>(vignette_texture.getSize().y)});
    vignette->setOrigin({vignette_texture.getSize().x / 2.0f, vignette_texture.getSize().y / 2.0f});
    vignette->setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
    
    // SOUND SETUP
    shoot_sound.emplace(shoot_sound_buffer);


    //LEGACY RANDOM SETUP
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // MAP GENERATION
    main_map = new map();
    main_map->generate();

    //PLAYER SETUP
    main_player = player(sf::Vector2f(4, 4), sf::Vector2f(1, 1), &player_texture, 100, 100);


    pistol_item = item_object(item(std::string("Pistol"), 1, 1, &pistol_texture,

        [](target& target_)
        {
            if(dungeon_shooter_game.getPlayer().getInventory().decreaseAmountOf("Bullet", 1))
            dungeon_shooter_game.bullets.push_back
            (
                bullet
                (
                    dungeon_shooter_game.getPlayer().getPosition(),
                    &dungeon_shooter_game.bullet_texture,
                    10,
                    0,
                    10.0f // speed
                )
            );
        }
    ),

    object({1.0f, 1.0f}, {1.0f, 1.0f}, &pistol_texture)

    );
    test_item = item_object(item(std::string("Bullet"), 128, 128, &bullet_texture), object(sf::Vector2f({10.0f, 0.0f}), sf::Vector2f({1.0f, 1.0f}), &bullet_texture));

    effect poison_effect = effect::Poison(600, 1);
    main_player.applyEffect(poison_effect);

    toUpdate.push_back(&main_player);

    window.setMouseCursorVisible(false);
}

//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================

// EVENT HANDLING FUNCTION
// IT HANDLES ALL THE EVENTS LIKE KEY PRESSES, MOUSE CLICKS, ETC.
void game::handleEvents()
{
    while(auto event = window.pollEvent())
    {
        // WINDOW CLOSED
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }

        // MOUSE BUTTON PRESSED
        if(event->is<sf::Event::MouseButtonPressed>())
        {
            auto mouse_event = event->getIf<sf::Event::MouseButtonPressed>();

            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f world_mouse_pos = window.mapPixelToCoords(mouse_pos);

            sf::Vector2f mouse_position = {world_mouse_pos.x / unit_size, world_mouse_pos.y / unit_size};

            target target_(nullptr, mouse_position);

            // LEFT BUTTON
            if(mouse_event->button == sf::Mouse::Button::Left)
            {
                main_player.getInventory().attackTriggered(target_);
            }

            //RIGHT BUTTON
            if(mouse_event->button == sf::Mouse::Button::Right)
            {
                main_player.getInventory().useTriggered(target_);
            }
        }

        // MOUSE WHEEL SCROLL
        if(event->is<sf::Event::MouseWheelScrolled>())
        {
            auto mouse_event = event->getIf<sf::Event::MouseWheelScrolled>();

            int delta = static_cast<int>(mouse_event->delta);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) main_player.getInventory().changeSelectedY(delta);
                else main_player.getInventory().changeSelectedX(delta);
            }
        }
    }
}

//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================


// UPDATE FUNCTION
// EACH FRAME (60 in 1 second) IT UPDATES GAME LOGIC
void game::update()
{
    unit_size = window.getSize().y / 9;

    //RANDOM TICK
    random_tick = static_cast<bool>(random_tick_dist(rnd));

    bool running = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Joystick::isButtonPressed(0, 0)) && main_player.canRun();

    sf::Vector2f move = input::getMovementDirection();

    sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x + sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) / 2, sf::Mouse::getPosition().y + sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V) / 2), window);


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

    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3) || sf::Joystick::isButtonPressed(0, 7)) && std::chrono::steady_clock::now() - last_debug_toggle > debug_toggle_cooldown)       
    {
        last_debug_toggle = std::chrono::steady_clock::now();
        debug_mode = !debug_mode;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2) && std::chrono::steady_clock::now() - last_screenshoot > screenshoot_cooldown)
    {
        last_screenshoot = std::chrono::steady_clock::now();
        takeScreenshoot();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
        spawnEnemy();
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

    if(test_item.collides(main_player))
    {
        test_item = main_player.getInventory().pickUpWithLeftover(test_item);
    }

    if(pistol_item.collides(main_player))
    {
        pistol_item = main_player.getInventory().pickUpWithLeftover(pistol_item);
    }

    updateEnemies();

    for(auto& a : toUpdate)
    {
        a->update();
    }
}


//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================

// RENDER FUNCTION
// IT DRAWS EVERYTHING ON THE SCREEN EACH FRAME
void game::render()
{
    // CLEARING THE WINDOW
    window.clear();

    //PLAYER POINT OF VIEW
    sf::View player_view
    (
        sf::Vector2f
        (
            (main_player.getPosition().x + 0.5f) * unit_size,
            (main_player.getPosition().y + 0.5f) * unit_size
        ),

        sf::Vector2f(window.getSize())
    );

    window.setView(player_view);

    // DRAWING THE WORLD
    window.draw(*floor);
    main_map->draw(window, main_player.getPosition());

    // DRAWING TEMPORARY ITEMS
    if(test_item.getAmount()) window.draw(test_item.rectangle());
    if(pistol_item.getAmount()) window.draw(pistol_item.rectangle());

    //PLAYER
    main_player.update();
    window.draw(main_player.rectangle());

    //ENEMIES
    for(auto& e : enemies)
    {
        window.draw(e.entity.rectangle());
    }

    //BULLETS
    for(auto& a : bullets)
    {
        window.draw(a.rectangle());
    }

    

    //GUI

    sf::View gui_view(sf::FloatRect({0.f, 0.f}, {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)}));
    window.setView(gui_view);

    //window.draw(*vignette);

    //TEMPORARY
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
    {
        main_player.getInventory().draw(window);
    }

    if(!debug_mode)
    {

        //EFFECTS
        main_player.drawActiveEffects(window);

        // CROSSHAIR
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        crosshair->setPosition(window.mapPixelToCoords(mouse_pos));
        window.draw(*crosshair);

        //HEALTH BAR
        sf::RectangleShape health_bar;
        health_bar.setSize({static_cast<float>(main_player.getHP()) / static_cast<float>(main_player.getMaxHP()) * static_cast<float>(unit_size), static_cast<float>(unit_size) / 2.0f});
        health_bar.setFillColor(sf::Color::Red);
        health_bar.setPosition({10.0f, static_cast<float>(window.getSize().y) - 100.0f});
        window.draw(health_bar);

        sf::Text health_text(main_font, std::to_string(main_player.getHP()), unit_size / 2.0f);
        health_text.setFillColor(sf::Color::Red);
        health_text.setPosition({15.0f + static_cast<float>(unit_size), static_cast<float>(window.getSize().y) - 100.0f});
        window.draw(health_text);

        
    }    
    else
    {
        //DEBUG MENU

        std::string debug_string = 
        "Unit size(px per tile): " + std::to_string(unit_size) + '\n'
        + "XY: " + std::to_string(main_player.getPosition().x) + " / " + std::to_string(main_player.getPosition().y) + '\n'
        + "Bullets: " + std::to_string(bullets.size()) + '\n'
        + "Stamina: " + std::to_string(main_player.Stamina()) + '\n'
        + "\n"
        + "Inventory:\n"
        + "Selected index: XY: " + std::to_string(main_player.getInventory().getSelectedX()) + " / " + std::to_string(main_player.getInventory().getSelectedY()) + '\n'
        + "Selected item: " + main_player.getInventory().getSelected().getName() + ' ' + std::to_string(main_player.getInventory().getSelected().getAmount()) + " / " + std::to_string(main_player.getInventory().getSelected().getMaxAmount()) + '\n';

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


//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================


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

//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================


player& game::getPlayer()
{
    return main_player;
}


std::vector<bullet>& game::getBullets()
{
    return bullets;
}


void game::spawnEnemy()
{
    sf::Vector2f player_pos = main_player.getPosition();

    sf::Vector2f spawn_pos = {player_pos.x - 25 + static_cast<float>(std::rand() % 50), player_pos.y - 25 + static_cast<float>(std::rand() % 50)};
    enemies.emplace_back(game::enemy{entity(spawn_pos, {1.0f, 1.0f}, &enemy_texture, 20, 20), sf::Vector2f(0.0f, 0.0f)});

    while(true)
    {    
        sf::Vector2f new_direction = {3 - std::rand() % 1, 3 - std::rand() % 1};
        if(new_direction.x != 0 || new_direction.y != 0)
        {
            enemies.back().direction = new_direction;
            break;
        }
    }
}

void game::updateEnemies()
{
    for(auto& e : enemies)
    {
        sf::Vector2f prev_pos = e.entity.getPosition();
        e.entity.move(e.direction * (1.0f / 60.0f) * 5.0f);
        if(main_map->collides(e.entity))
        {
            e.entity.teleport(prev_pos);
            do
            {
                e.direction =
                {
                    static_cast<float>(std::rand() % 3 - 1),
                    static_cast<float>(std::rand() % 3 - 1)
                };
            } while(e.direction.x == 0 && e.direction.y == 0);

        }

        e.entity.update();
    }
}


// JUNK

/*if(mouse_event->button == sf::Mouse::Button::Left && main_player.getInventory().getAmountOf("Bullet") > 0)
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

    if(!main_player.getInventory().decreaseAmountOf("Bullet", 1)) throw std::runtime_error("Something went wrong :(");
}*/

/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -50)
{
    move.y -= 1;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 50)
{
    move.y += 1;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A ) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50)
{
    move.x -= 1;
}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50)
{
    move.x += 1;
}*/