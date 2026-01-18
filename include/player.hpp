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

    public:        

        using entity::entity;

        void operator=(const player& other);

        void changeWeapon(WEAPON new_weapon);

        void changeWeapon(int delta);

        WEAPON getCurrentWeapon() const;
    };

#endif // PLAYER_HPP