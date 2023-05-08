
#ifndef COWBOY_VS_NINJA_A_TRAINEDNINJA_HPP
#define COWBOY_VS_NINJA_A_TRAINEDNINJA_HPP

#include "Ninja.hpp"

class TrainedNinja : public Ninja {


public:

    TrainedNinja(string name, Point &&location);

    TrainedNinja(string name, Point &location);
};

#endif //COWBOY_VS_NINJA_A_TRAINEDNINJA_HPP
