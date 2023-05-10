
#ifndef COWBOY_VS_NINJA_A_TEAM_HPP
#define COWBOY_VS_NINJA_A_TEAM_HPP


#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include "Point.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"

namespace ariel{}

class Team {

protected:

    std::list<Character*> members[10];
    Character *leader;

public:

    explicit Team(Character *leader);

    void add(Character *newMember);

    virtual void attack(Team *enemyTeam);

    int stillAlive();

    virtual void print();

    ~Team();

};


#endif //COWBOY_VS_NINJA_A_TEAM_HPP
