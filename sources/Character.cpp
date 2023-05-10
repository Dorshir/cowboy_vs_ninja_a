#include "Character.hpp"

#include <utility>

Point &Character::getLocation() {
    return location;
}

string Character::getName() {
    return {};
}

void Character::hit(int hitNum) {

}

double Character::distance(Character *other) {
    return 0;
}

bool Character::isAlive() {
    return false;
}


Character::Character(string name, int hitpoints, Point &location) : location(location), hitPoints(hitpoints),
                                                                    name(std::move(name)) {
}

Character::~Character() = default;

