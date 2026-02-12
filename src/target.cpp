#include "../include/target.hpp"

target::target(entity* target_entity, sf::Vector2f target_raw_position) : target_entity{target_entity}, target_raw_position{target_raw_position}
{

}

entity* target::getTargetEntity()
{
    return this->target_entity;
}

sf::Vector2f target::getTargetRawPosition()
{
    return this->target_raw_position;
}