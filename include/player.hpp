#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "inventory.hpp"

//PLAYER
    class player : public entity
    {
    private:

        float stamina = 5.0f;
        float stamina_limit = 5.0f;

        inventory inventory_;

    public:        

        using entity::entity;

        void operator=(const player& other);

        bool canRun();

        void increaseStamina(float delta);

        void decreaseStamina(float delta);

        inventory& getInventory();

        float Stamina();
    };

#endif // PLAYER_HPP