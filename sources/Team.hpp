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
    Point(double parX, double parY);
    double distance(Point point);
    string print() const;
    static Point moveTowards(Point src, Point des, double dis);
    double getX();
    double getY();
    bool operator==(const Point& other) const;


};

class Character {
protected:
    Point pos;
    int hitPoint;
    string name;
    bool team;

public:
    Character();
    Character(const string &name, const Point &pos, int hitPoint);
    virtual ~Character();
    Character(const Character &other); //copy
    Character &operator=(const Character& other); //Copy assignment operator
    Character(Character&& other) noexcept; //Move constructor
    Character &operator=(Character&& other) noexcept; //Move assignment operator

    bool isAlive() const;
    double distance(const Character *character) ;
    void hit(int num);
    string getName();
    Point getLocation();
    int getHitPoint();
    virtual string print() const;
    virtual void attack(Character *enemy);
    bool inTeam();
    void setTeam(bool ist);
    friend bool operator==(const Character& ch1, const Character& ch2);


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
    void attack(Character *enemy) override;
    string print() const override;
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
    void attack(Character *enemy) override;
    string print() const override;
    int getSpeed();
};

class YoungNinja: public Ninja {
public:
    YoungNinja(const string &name, const Point &pos);
};

class TrainedNinja : public Ninja {
public:
    TrainedNinja(const string &name, const Point &pos);
};

class OldNinja: public Ninja {
public:
    OldNinja(const string &name, const Point &pos);
};


class Team {
protected:
    vector<Character*> teamMates;
    Character *leader;
public:
    Team(Character *leader);
    virtual ~Team(); //Destructor
    Team(const Team &other); //copy
    Team &operator=(const Team &other); //Copy assignment operator
    Team(Team &&other) noexcept; //Move constructor
    Team &operator=(Team &&other) noexcept; //Move assignment operator


    void add(Character *character);
    virtual void attack(Team *enemy);
    int stillAlive() const;
    void print();
    void nextLeader();
    Character *getLeader();
    Character* closest(Team *team);
    vector<Character*> sort(vector<Character*> list);

    friend ostream &operator <<(ostream &output, const Team &team);

};

class Team2: public Team{
public:
    Team2(Character *leader): Team(leader){}
    vector<Character*> sort(vector<Character*> list);
};

class SmartTeam: public Team {
    SmartTeam(Character *leader): Team(leader){}
    void attack(Team *enemy) override;
    vector<Character*> smartSort(vector<Character*> list, Character *enemy);
};


#endif //COWBOY_VS_NINJA_A_TEAM_HPP




