
#ifndef COWBOY_VS_NINJA_A_NINJA_HPP
#define COWBOY_VS_NINJA_A_NINJA_HPP


#include "Character.hpp"

class Ninja : public Character {

private:

    int speed;

public:

    void setSpeed(int newSpeed);

    int getSpeed();

    Ninja(string name, int hitpoints, Point &location, int speed);

    void move(Character *enemy);

    void slash(Character *enemy);

};

#endif //COWBOY_VS_NINJA_A_NINJA_HPP
