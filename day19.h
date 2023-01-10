#pragma once

#include "common.h"

struct Vector3 {
    int x, y, z;

    std::array<Vector3, 24> possible_configs() const;
    int16_t distanceTo(Vector3 other) const;

    size_t operator()(const Vector3& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    bool operator==(const Vector3& other) const {
        return std::tie(x, y, z) == std::tie(other.x, other.y, other.z);
    }

    Vector3() : x(0), y(0), z(0) {}
    Vector3(int a, int b, int c) : x(a), y(b), z(c) {}
    Vector3(std::vector<int> v) : x(v[0]), y(v[1]), z(v[2]) {}
    Vector3(std::string s) : Vector3(split_string<int>(s, ",", [](const std::string s) {return std::stoi(s);})) {}
};
std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << "{" << v.x << "," << v.y << "," << v.z << "}";
    return os;
}

struct Scanner {    
    std::vector<Vector3> beacons;
    std::unordered_map<int16_t, std::pair<Vector3, Vector3>> distances_map;
    std::function<Vector3(Vector3)> f;
    Vector3 position;

    std::vector<Vector3> differentials() const ;
    void computeDistances();
    Vector3 getOtherPosition(Scanner& other);
};
std::ostream& operator<<(std::ostream& os, const Scanner& s) {
    os << "Scanner : " << s.beacons;
    return os;
}

struct day19 {
    std::vector<Scanner> scanners;
    std::vector<Vector3> scanners_positions;
    std::unordered_set<Vector3, Vector3> totalBeacons;

    day19();

    void part_one();
    void part_two();
};