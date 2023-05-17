#include "Character.hpp"

#include <utility>

Point &Character::getLocation() {
    return location;
}

string Character::getName() {
    return name;
}

void Character::hit(int hitNum) {
}

double Character::distance(Character *other) {
    return 0;
}

bool Character::isAlive() {
    return false;
}

int getHitPoints(){
    return 1;
}


Character::Character(string name, int hitpoints, Point &location) : location(location), hitPoints(hitpoints),
                                                                    name(std::move(name)) {
}


Character::Character(const Character& other)
    : location(other.location), hitPoints(other.hitPoints), name(other.name) {
}


Character& Character::operator=(const Character& other){

    return *this;
}

Character::Character(Character&& other) noexcept
    : location(std::move(other.location)), hitPoints(std::move(other.hitPoints)), name(std::move(other.name)) {
}

Character& Character::operator=(Character&& other) noexcept {
    
    return *this;
}