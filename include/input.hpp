#ifndef INPUT_HPP
#define INPUT_HPP

#include "headers.hpp"

class input
{
public:

    static sf::Vector2f getMovementDirection();

    static bool isDebugButtonPressed();
};

#endif // INPUT_HPP