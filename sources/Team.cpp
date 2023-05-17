#include "Team.hpp"


void Team::add(Character *newMember) {

}

Team::Team(Character *leader) : leader(leader) {
    members.resize(10, nullptr);

}

void Team::attack(Team *enemyTeam) {

}

int Team::stillAlive() {
    return 0;
}

void Team::print() {

}

Team::~Team() = default;

void Team::setLeader(Character* newLeader){
    leader = newLeader;
}

Character* Team::getLeader(){
    return leader;
}

vector<Character*> Team::getMembers(){
    return members;
}
