
#include "Ninja.hpp"

#include <utility>

Ninja::Ninja(string name, int hitpoints, Point &location, int speed) : speed(speed),
                                                                       Character(std::move(name), hitpoints, location) {}

void Ninja::move(Character *enemy) {

}

void Ninja::slash(Character *enemy) {

}

