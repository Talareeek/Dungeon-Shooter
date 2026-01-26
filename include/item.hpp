#ifndef ITEM_HPP
#define ITEM_HPP

#include "headers.hpp"

#include "object.hpp"

class item
{
private:

    std::string name = "";
    size_t max_amount = 0;
    size_t amount = 0;
    
    sf::Texture* texture = nullptr;

    std::function <void(object&)> onAttack = [](object& target){};
    std::function <void(object&)> onUse = [](object& target){};

public:

    item();

    item(std::string name, size_t max_amount, size_t amount, sf::Texture* texture, std::function <void(object&)> onAttack = [](object& target){}, std::function <void(object&)> onUse = [](object& target){});

    item& operator=(const item& other);

    std::string getName();

    size_t getMaxAmount();

    size_t getAmount();

    sf::Texture* getTexture();

    item increaseAmountWithLeftover(size_t delta);

    size_t decreaseAmountWithLeftover(size_t delta);

    void changeAmount(long long delta);

    void setAmount(size_t amount);

    void attackTriggered(object& target);

    void useTriggered(object& target);
};

#endif // ITEM_HPP