//
// Created by HOME on 02/05/2023.
//

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

    virtual bool isAlive();

    virtual double distance(Character *other);

    virtual void hit(int hitNum);

    virtual string getName();

    virtual Point& getLocation();

    virtual string print();

    ~Character();


};

#endif //COWBOY_VS_NINJA_A_CHARACTER_HPP
