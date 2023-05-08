#include "TrainedNinja.hpp"

#include <utility>

TrainedNinja::TrainedNinja(string name, Point &location) : Ninja(std::move(name), 120, location, 12) {}

TrainedNinja::TrainedNinja(string name, Point &&location) : Ninja(std::move(name), 120, location, 12) {}
