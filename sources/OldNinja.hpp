
#ifndef COWBOY_VS_NINJA_A_OLDNINJA_HPP
#define COWBOY_VS_NINJA_A_OLDNINJA_HPP

#include "Ninja.hpp"

class OldNinja : public Ninja {

public:

    OldNinja(string name, Point &&location);

    OldNinja(string name, Point &location);
};

#endif //COWBOY_VS_NINJA_A_OLDNINJA_HPP
