#ifndef ITEM_HPP
#define ITEM_HPP

#include "headers.hpp"

#include "object.hpp"

#include "target.hpp"

class item
{
private:

    std::string name = "";
    size_t max_amount = 0;
    size_t amount = 0;
    
    sf::Texture* texture = nullptr;

    std::function <void(target&)> onAttack = [](target& target_){};
    std::function <void(target&)> onUse = [](target& target_){};

public:

    item();

    item(std::string name, size_t max_amount, size_t amount, sf::Texture* texture, std::function <void(target&)> onAttack = [](target& target_){}, std::function <void(target&)> onUse = [](target& target_){});

    item& operator=(const item& other);

    std::string getName();

    size_t getMaxAmount();

    size_t getAmount();

    sf::Texture* getTexture();

    item increaseAmountWithLeftover(size_t delta);

    size_t decreaseAmountWithLeftover(size_t delta);

    void changeAmount(long long delta);

    void setAmount(size_t amount);

    void attackTriggered(target& target_);

    void useTriggered(target& target_);
};

#endif // ITEM_HPP