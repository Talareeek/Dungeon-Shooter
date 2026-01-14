#ifndef BULLET_HPP
#define BULLET_HPP

#include "object.hpp"

class bullet : public object
{
private:

    uint8_t damage;
    float speed;
    float direction_angle;

public:

    bullet(sf::Vector2f position, sf::Texture* texture, uint8_t damage, float direction_angle, float speed);

    void update();

};

#endif // BULLET_HPP

/*
    struct bullet

        

        bullet(sf::Vector2f start_pos, sf::Texture* texture, float scale, uint8_t damage_value,  float direction_angle, float speed);

        void update(float delta_time);
    };
*/