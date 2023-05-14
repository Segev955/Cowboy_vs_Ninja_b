//
// Created by segev95 on 04/05/2023.
//


#include "Team.hpp"

using namespace ariel;

Point::Point(double x, double y): x(x), y(y) {}

double Point::distance(Point p) {
    double a = pow(p.x - this->x, 2);
    double b = pow(p.y - this->y, 2);
    return sqrt(a + b);
}

string Point::print() const{
    return "(" + to_string(this->x) + "," + to_string(this->y)  + ")";
}

Point moveTowards(Point src, Point des, double dis) {
    double srcToDes = src.distance(des);
    if (dis >= srcToDes) {
        return des;
    }
    //not finish
    return Point(1,1);
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

//Equal
bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}




