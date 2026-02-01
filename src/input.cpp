#include "../include/input.hpp"

sf::Vector2f input::getMovementDirection()
{
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -50.f)
        direction.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 50.f)
        direction.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50.f)
        direction.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50.f)
        direction.x += 1.f;

    if (direction.x != 0.f || direction.y != 0.f)
    {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;
    }

    return direction;
}

bool input::isDebugButtonPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3) || sf::Joystick::isButtonPressed(0, 7);
}