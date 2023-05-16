//
// Created by segev95 on 04/05/2023.
//

#include "Team.hpp"

Team::Team(Character *leader) : leader(leader) {
//    if (leader->inTeam()) {
//        throw runtime_error("this teammates is already in a team");
//    }
    this->add(leader);
    leader->setTeam(true);
}

void Team::add(Character *character) {
    if (character->inTeam()) {
        throw runtime_error("this teammates is already in a team");
    }
    if (this->teamMates.size() >= 10) {
        throw runtime_error("Can't add more the 10 teammates");
    } else {
        this->teamMates.push_back(character);
        character->setTeam(true);
    }

}


void Team::nextLeader() {
    if (this->leader->isAlive()) {
        return;
    }
    Character *c = nullptr;
    double minDis = DBL_MAX;
    for (std::size_t i = 0; i < teamMates.size(); ++i) {
        if (teamMates[i]->distance(leader) < 0 || !teamMates[i]->isAlive())
            continue;
        if (teamMates[i]->distance(leader) < minDis) {
            minDis = teamMates[i]->distance(leader);
            c = teamMates[i];
        }
    }
    leader = c;
}

Character *Team::closest(Team *team) {
    double minDis = DBL_MAX;
    Character *c = nullptr;
    for (std::size_t i = 0; i < team->teamMates.size(); ++i) {
        if (team->teamMates[i]->isAlive() && team->teamMates[i]->distance(leader) < minDis) {
            minDis = team->teamMates[i]->distance(leader);
            c = team->teamMates[i];
        }
    }
    return c;
}

vector<Character *> Team::sort(vector<Character *> list) {
    vector<Character *> newList;
    //first - cowboys:
    for (Character* c : list) {
        if (Cowboy* cowboy = dynamic_cast<Cowboy*>(c)) {
            if (cowboy->isAlive())
                newList.push_back(cowboy);
        }
    }
    //second - ninjas:
    for (Character* c : list) {
        if (Ninja* ninja = dynamic_cast<Ninja*>(c)) {
            if (ninja->isAlive())
                newList.push_back(ninja);
        }
    }
    return newList;
}

void Team::attack(Team *enemy) {

    if (enemy == nullptr) {
        throw invalid_argument("enemy = null");
    }
    if (stillAlive() == 0 || enemy->stillAlive() == 0) {
        throw runtime_error("The whole team is dead");
    }
//    cout << "S***********:    ";

    nextLeader();
    if (!this->leader->isAlive())
        return;
    vector<Character *> newTeammates = sort(this->teamMates);
    for (Character* player : newTeammates) {
        enemy->nextLeader();
//        cout << enemy->leader->print() << endl;
        if (!enemy->leader->isAlive()) {
            break;
        }
        Character *c = closest(enemy);
        if(c == nullptr || !c->isAlive()) {
            continue;
        }
        player->attack(c);
    }
    enemy->nextLeader();
}


int Team::stillAlive() const {
    int c = 0;
    for (std::size_t i = 0; i < teamMates.size(); ++i) {
        if (teamMates[i]->isAlive()) {
            c++;
        }
    }
    return c;
}

void Team::print() const {
    cout << *this << endl;
}

ostream &operator<<(ostream &output, const Team &team) {
    for (auto item: team.teamMates) {
        output << *item;
    }
    return output;
}


