#include "YoungNinja.hpp"

#include <utility>

YoungNinja::YoungNinja(string name, Point &location) : Ninja(std::move(name), 100, location, 14) {}

YoungNinja::YoungNinja(string name, Point&& location): Ninja(std::move(name), 100, location, 14) {}

string YoungNinja::print() {return "";}

