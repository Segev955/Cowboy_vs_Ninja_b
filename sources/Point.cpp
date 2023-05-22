//
// Created by segev95 on 04/05/2023.
//


#include "Team.hpp"

using namespace ariel;

//Constructor
Point::Point(double parX, double parY): x(parX), y(parY) {}

double Point::distance(Point point) { //sqrt((x1-x2)^2 + (y1-y2)^2)
    double a = pow(point.x - this->x, 2);
    double b = pow(point.y - this->y, 2);
    return sqrt(a + b);
}

string Point::print() const{
    return "(" + to_string(this->x) + "," + to_string(this->y)  + ")";
}

Point Point::moveTowards(Point src, Point des, double dis) {
    if (dis < 0) {
        throw invalid_argument("Negative distance");
    }
    double srcToDes = src.distance(des);
    if (dis >= srcToDes) { //if less than 'dis -> arrive to destination
        return des;
    }
    //move close as you can:
    double X = des.x - src.x;
    double Y = des.y - src.y;
    double len = sqrt(X*X + Y*Y);

    double moveX = X / len * dis;
    double moveY = Y / len * dis;
    return Point(src.x + moveX, src.y + moveY);
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






