#include "OldNinja.hpp"

#include <utility>

OldNinja::OldNinja(string name, Point &&location) : Ninja(std::move(name), 150, location, 8) {}

OldNinja::OldNinja(string name, Point &location) : Ninja(std::move(name), 150, location, 8) {}

string OldNinja::print() {
    return "";
}

OldNinja::~OldNinja() = default;
