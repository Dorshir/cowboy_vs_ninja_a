
#ifndef COWBOY_VS_NINJA_A_YOUNGNINJA_HPP
#define COWBOY_VS_NINJA_A_YOUNGNINJA_HPP

#include "Ninja.hpp"

class YoungNinja : public Ninja {

public:

    YoungNinja(string name, Point &location);

    YoungNinja(string name, Point &&location);

    string print() override;

};

#endif //COWBOY_VS_NINJA_A_YOUNGNINJA_HPP
