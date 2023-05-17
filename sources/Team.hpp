
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

private:

    std::vector<Character*> members;

    Character *leader;

public:

    void setLeader(Character* newLeader);

    Character* getLeader();

    vector<Character*> getMembers();

    explicit Team(Character *leader);

    void add(Character *newMember);

    virtual void attack(Team *enemyTeam);

    int stillAlive();

    virtual void print();

    virtual ~Team();

    Team(const Team& other) = default;

    Team& operator=(const Team& other) = default;

    Team(Team&& other) = default;

    Team& operator=(Team&& other) = default;

};


#endif //COWBOY_VS_NINJA_A_TEAM_HPP
