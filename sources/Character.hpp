
#ifndef COWBOY_VS_NINJA_A_CHARACTER_HPP
#define COWBOY_VS_NINJA_A_CHARACTER_HPP

#include "Point.hpp"
#include <string>

using namespace std;

class Character {

protected:

    Point location;
    int hitPoints;
    string name;

public:

    Character(string name, int hitpoints, Point &location);

    bool isAlive();

    double distance(Character *other);

    void hit(int hitNum);

    string getName();

    Point& getLocation();

    virtual string print() = 0;

    virtual ~Character();

};

#endif //COWBOY_VS_NINJA_A_CHARACTER_HPP
