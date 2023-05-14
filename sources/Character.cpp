//
// Created by segev95 on 04/05/2023.
//

#include "Team.hpp"

using namespace ariel;

Character::Character() : pos(0, 0), hitPoint(0), team(false) {}

//constructor
Character::Character(const string &name, const Point &pos, const int hitPoint) : name(name), pos(pos),
                                                                                 hitPoint(hitPoint), team(false) {}

bool Character::isAlive() const {
    if (hitPoint > 0)
        return true;
    return false;
}

double Character::distance(const Character *c) {
    return this->pos.distance(c->pos);
}

void Character::hit(int num) {
    if (num < 0) {
        throw invalid_argument("hit: number cant be negative");
    }
    this->hitPoint -= num;
}

string Character::getName() {
    return this->name;
}

Point Character::getLocation() {
    return this->pos;
}

int Character::getHitPoint() {
    return this->hitPoint;
}

string Character::print() const {
    if (!isAlive()) {
        return '(' + name + ')';
    } else {
        return "name: " + name + "\nhitPoint: " + to_string(hitPoint) + "\npos: " + pos.print() + "\n";
    }
}

void Character::attack(Character *enemy) {}

bool Character::inTeam() {
    return team;
}

void Character::setTeam(bool is) {
    team = is;
}

bool operator==(const Character& c1, const Character& c2) {
    return &c1 == &c2;
}

//Output
ostream &operator<<(ostream &output, const Character &character) {
    output << character.print();
    return output;
}

//Cowboy ----------------------------------------------------
Cowboy::Cowboy(const string &name, const Point &pos) : Character(name, pos, 110), bullets(6) {}

void Cowboy::shoot(Character *enemy) {
    if (*this == *enemy) {
        throw runtime_error("Can't attack yourself");
    }
    if (!enemy->isAlive() || !isAlive()) {
        throw runtime_error("The Character is dead");
    }
    if (isAlive() && hasboolets()) {
        enemy->hit(10);
        bullets--;
    } else if (!hasboolets()) {
        reload();
    }
}

bool Cowboy::hasboolets() {
    if (this->bullets > 0)
        return true;
    return false;
}

void Cowboy::reload() {
    if (!isAlive()) {
        throw runtime_error("The Character is dead");
    }
    this->bullets = 6;
}

void Cowboy::attack(Character *enemy) {
    shoot(enemy);
}

string Cowboy::print() const {
    if (!isAlive()) {
        return "--C--\nname: (" + name + ")\npos: " + pos.print() + "\nBullets: " +
               to_string(bullets) + "\n";
    } else {
        return "--C--\nname: " + name + "\nhitPoint: " + to_string(hitPoint) + "\npos: " + pos.print() + "\nBullets: " +
               to_string(bullets) + "\n";
    }
}

int Cowboy::getBullets() {
    return bullets;
}

//Cowboy ----------------------------------------------------

//Ninja -----------------------------------------------------
Ninja::Ninja(const string &name, const Point &pos, int hitPoint, int speed) : Character(name, pos, hitPoint),
                                                                              speed(speed) {}

void Ninja::move(Character *enemy) {
    this->pos = moveTowards(this->getLocation(), enemy->getLocation(), this->speed);
}

void Ninja::slash(Character *enemy) {
    if (*this == *enemy) {
        throw runtime_error("Can't attack yourself");
    }
    if (!enemy->isAlive() || !isAlive()) {
        throw runtime_error("The Character is dead");
    }
    if (isAlive() && this->getLocation().distance(enemy->getLocation()) < 1) {
        enemy->hit(40);
    } else if (this->getLocation().distance(enemy->getLocation()) >= 1) {
        move(enemy);
    }
}

void Ninja::attack(Character *enemy) {
    slash(enemy);
}

string Ninja::print() const {
    if (!isAlive()) {
        return "--N--\nname: (" + name + ")\npos: " + pos.print() + "\nSpeed: " +
               to_string(speed) + "\n";
    } else {
        return "--N--\nname: " + name + "\nhitPoint: " + to_string(hitPoint) + "\npos: " + pos.print() + "\nSpeed: " +
               to_string(speed) + "\n";
    }
}

int Ninja::getSpeed() {
    return speed;
}

//Ninja -----------------------------------------------------


