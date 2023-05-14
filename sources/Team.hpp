//
// Created by segev95 on 04/05/2023.
//

#ifndef COWBOY_VS_NINJA_A_TEAM_HPP
#define COWBOY_VS_NINJA_A_TEAM_HPP

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <cfloat>


namespace ariel {}
using namespace std;


class Point {
private:
    double x;
    double y;

public:
    Point(double x, double y);
    double distance(Point p);
    string print() const;
    friend Point moveTowards(Point src, Point des, double dis);
    double getX();
    double getY();
    bool operator==(const Point& other) const;


};

class Character {
protected:
    Point pos;
    int hitPoint;
    string name;

public:
    Character();
    Character(const string &name, const Point &pos, const int hitPoint);
    bool isAlive() const;
    double distance(const Character *c) ;
    void hit(int num);
    string getName();
    Point getLocation();
    int getHitPoint();
    virtual string print() const;
    virtual void attack(Character *enemy);

    friend ostream &operator <<(ostream &output, const Character &character);

};
//Cowboy:
class Cowboy: public Character {
private:
    int bullets;

public:
    Cowboy(const string &name, const Point &pos); //6 bullets, 110 hitPoints.
    void shoot(Character *enemy);
    bool hasboolets();
    void reload();
    void attack(Character *enemy);
    string print() const;
    int getBullets();
};
//ninja:
class Ninja: public Character {
private:
    int speed;
public:
    Ninja (const string &name, const Point &pos, int hitPoint, int speed);
    void move(Character *enemy);
    void slash(Character *enemy);
    void attack(Character *enemy);
    string print() const;
    int getSpeed();
};

class YoungNinja: public Ninja {
public:
    YoungNinja(const string &name, const Point &pos) : Ninja(name,pos,100, 14){}
};

class TrainedNinja : public Ninja {
public:
    TrainedNinja(const string &name, const Point &pos) : Ninja(name,pos,120, 12){}
};

class OldNinja: public Ninja {
public:
    OldNinja(const string &name, const Point &pos) : Ninja(name,pos,150, 8){}
};


class Team {
private:
    vector<Character*> teamMates;
    Character *leader;
public:
    Team(Character *leader);
    void add(Character *c);
    void attack(Team *enemy);
    int stillAlive() const;
    void print() const;
    void nextLeader();
    Character* closest(Team *team);

    friend ostream &operator <<(ostream &output, const Team &team);

};

class Team2: public Team{
    Team2(Character *leader);
};


#endif //COWBOY_VS_NINJA_A_TEAM_HPP


