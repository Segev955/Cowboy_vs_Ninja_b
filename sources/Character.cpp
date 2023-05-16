//
// Created by segev95 on 04/05/2023.
//

#include "Team.hpp"

using namespace ariel;

Character::Character() : pos(0, 0), hitPoint(0), team(false) {}

//constructor
Character::Character(const string &name, const Point &pos, int hitPoint) : name(name), pos(pos),
                                                                           hitPoint(hitPoint), team(false) {}
//destructor
Character::~Character() {}

//Copy constructor
Character::Character(const Character &other) : pos(other.pos) {
    this->name = other.name;
    this->hitPoint = other.hitPoint;
    this->team = other.team;
}

//Copy assignment operator
Character &Character::operator=(const Character &other) {
    if (this != &other) {
        this->name = other.name;
        this->pos = other.pos;
        this->hitPoint = other.hitPoint;
        this->team = other.team;
    }
    return *this;
}

//Move constructor
Character::Character(Character &&other) noexcept : pos(move(other.pos)) { //cant Throw
this->name = move(other.name);
this->hitPoint = other.hitPoint;
this->team = other.team;
}

//Move assignment operator
Character& Character::operator=(Character&& other) noexcept {
if (this != &other) {
this->name = move(other.name);
this->pos = move(other.pos);
this->hitPoint = other.hitPoint;
this->team = other.team;
}
return *this;
}

bool Character::isAlive() const {
    if (hitPoint > 0)
        return true;
    return false;
}

double Character::distance(const Character *character) {
    return this->pos.distance(character->pos);
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

void Character::setTeam(bool ist) {
    team = ist;
}

bool operator==(const Character& ch1, const Character& ch2) {
    return &ch1 == &ch2;
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

YoungNinja::YoungNinja(const string &name, const Point &pos) : Ninja(name,pos,100, 14){}

TrainedNinja::TrainedNinja(const string &name, const Point &pos) : Ninja(name,pos,120, 12){}

OldNinja::OldNinja(const string &name, const Point &pos) : Ninja(name,pos,150, 8){}

//Ninja -----------------------------------------------------


