
#ifndef COWBOY_VS_NINJA_A_CHARACTER_HPP
#define COWBOY_VS_NINJA_A_CHARACTER_HPP

#include "Point.hpp"
#include <string>

using namespace std;

class Character {
    
private:

    Point location;
    int hitPoints;
    string name;

public:

    Character(string name, int hitpoints, Point& location);
    Character(const Character& other);
    Character(Character&& other) noexcept;
    Character& operator=(const Character& other);
    Character& operator=(Character&& other) noexcept;

    bool isAlive();
    double distance(Character* other);
    void hit(int hitNum);

    // Getters
    int getHitPoints();
    string getName();
    Point& getLocation();

    // Setters
    void setName(const string& newName);
    void setHitPoints(int newHitPoints);
    void setLocation(const Point& newLocation);

    virtual string print() = 0;
    virtual ~Character() = default;
};

#endif //COWBOY_VS_NINJA_A_CHARACTER_HPP
