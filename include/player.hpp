#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

//PLAYER
    class player : public entity
    {
    public:

        enum class WEAPON
        {
            RIFLE,
            SHOTGUN,
            SNIPER
        };

    private:

        WEAPON current_weapon = WEAPON::RIFLE;

        float stamina = 5.0f;
        float stamina_limit = 5.0f;

    public:        

        using entity::entity;

        void operator=(const player& other);

        void changeWeapon(WEAPON new_weapon);

        void changeWeapon(int delta);

        WEAPON getCurrentWeapon() const;

        bool canRun();

        void increaseStamina(float delta);

        void decreaseStamina(float delta);

        float Stamina();
    };

#endif // PLAYER_HPP