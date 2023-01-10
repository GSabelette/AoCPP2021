#pragma once

#include "common.h"

struct Point {
    int coordX;
    int coordY;

    Point() : coordX(-1), coordY(-1) {};
    Point(std::string s);
};
std::ostream& operator<<(std::ostream& os, Point p) {
    os << "Point {" << p.coordX << ", " << p.coordY << "}";
    return os;
}
constexpr bool operator ==(const Point& p1, const Point& p2) {
    return (p1.coordX == p2.coordX) && (p1.coordY == p2.coordY);
}

struct Line {
    Point first_point;
    Point second_point;

    Line(std::string s);

    bool is_vertical() {return first_point.coordX == second_point.coordX;}
    bool is_horizontal() {return first_point.coordY == second_point.coordY;}
};
std::ostream& operator<<(std::ostream& os, Line l) {
    os << "Line {" << l.first_point << " | " << l.second_point << "}";
    return os;
}
constexpr bool operator ==(const Line& l1, const Line& l2) {
    return (l1.first_point == l2.first_point) && (l1.second_point == l2.second_point);
}

struct day05 {
    std::unordered_map<std::pair<int,int>, int, PairHash<int,int>> map;
    std::vector<Line> input; 

    day05();

    void part_one();
    void part_two();
};