#pragma once

#include "common.h"

#define HALLWAY_SIZE 11
#define PT1_SIZE 19
#define ROOM_SIZE_PT_1 2
#define NB_ROOMS 4

std::unordered_map<char, int> costsMap {{'A',1}, {'B',10}, {'C',100}, {'D',1000}};
std::unordered_set<int> frontRooms {2,4,6,8};
std::unordered_map<int, int> roomFrontMap {
    {11, 2}, {15, 2},
    {12, 4}, {16, 4},
    {13, 6}, {17, 6},
    {14, 8}, {18, 8}
};
std::unordered_map<char, std::set<int>> destinationsMap {
    {'A',{11,15}},
    {'B',{12,16}},
    {'C',{13,17}},
    {'D',{14,18}}
};

bool inRoom(int pos) {return pos>=11;}

struct Plan {
    std::array<char, 19> hallway;

    bool is_alive(int i) const {return (hallway[i] != '.');}
    std::vector<int> get_alive() const;

    std::vector<int> adjacences(int p) const;

    std::vector<int> moveIn(int pos) const;
    std::vector<int> moveOut(int pos) const;

    void swap_places(int i, int j);

    bool operator==(const Plan& other) const {
        return hallway == other.hallway;
    }
    size_t operator()(const Plan& p) const {
        size_t hash = 0;
        for (auto& c : hallway) hash ^= std::hash<char>()(c);
        return hash;
    }
};

struct day23 {
    Plan p;
    Plan end;

    void explore();

    day23();

    void part_one();
    void part_two();
};