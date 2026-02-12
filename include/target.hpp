#ifndef TARGET_HPP
#define TARGET_HPP

#include "entity.hpp"
#include "headers.hpp"

class target
{
private:

    entity* target_entity;
    sf::Vector2f target_raw_position;

public:

    target(entity* target_entity, sf::Vector2f target_raw_position);

    entity* getTargetEntity();

    sf::Vector2f getTargetRawPosition();
};

#endif // TARGET_HPP