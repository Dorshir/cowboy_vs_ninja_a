//
// Created by HOME on 02/05/2023.
//

#ifndef COWBOY_VS_NINJA_A_COWBOY_HPP
#define COWBOY_VS_NINJA_A_COWBOY_HPP


#include "Character.hpp"

class Cowboy : public Character {

    Cowboy(string name, Point &&location);

    int booletsNum;

public:

    Cowboy(string name, Point &location);

    void shoot(Character *enemy);

    bool hasboolets();

    void reload();


};

#endif //COWBOY_VS_NINJA_A_COWBOY_HPP
