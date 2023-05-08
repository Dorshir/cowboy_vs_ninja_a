
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

    std::list<Character> members;
    Character *leader;

public:

    explicit Team(Character *leader);

    void add(Cowboy *newMember);

    void add(Ninja *newMember);

    void attack(Team *enemyTeam);

    int stillAlive();

    void print();

    ~Team();

};


#endif //COWBOY_VS_NINJA_A_TEAM_HPP
