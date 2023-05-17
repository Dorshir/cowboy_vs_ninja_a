#include "Cowboy.hpp"

#include <utility>

Cowboy::Cowboy(string name, Point &location) : booletsNum(6), Character(std::move(name),110,location) {}

Cowboy::Cowboy(string name, Point &&location) : booletsNum(6), Character(std::move(name),110,location) {}

void Cowboy::shoot(Character *enemy) {

}

bool Cowboy::hasboolets() {
    return false;
}

void Cowboy::reload() {

}

string Cowboy::print() {
    return "";
}

