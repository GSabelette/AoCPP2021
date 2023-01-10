#pragma once

#include "common.h"

struct Player {
    int pos = 1;
    int score = 0;
    Player(int p) : pos(p) {}
    Player() {}
    bool operator==(const Player& other) const {
        return (pos == other.pos && score == other.score); 
    }
};

struct Universe {
    Player p[2];
    int64_t count = 1;
    int curPlayer = 0;

    size_t operator()(const Universe& u) const {
        return (std::hash<int>()(p[0].pos) ^ std::hash<int>()(p[0].score)) ^ ((std::hash<int>()(p[1].pos) ^ std::hash<int>()(p[1].pos)) << 1);
    }
    bool operator==(const Universe& other) const {
        return (p[0] == other.p[0] && p[1] == other.p[1]);
    }
    Universe(Player p0, Player p1) : p{p0, p1} {}
};

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "{" << p.pos << "," << p.score << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Universe& u) {
    os << "U{P1:" << u.p[0] << ",P2" << u.p[1] << ",count:" << u.count << "}";
    return os;
}

struct day21 {
    int diceValue = 0;
    int pos1;
    int pos2;

    day21();

    void part_one();
    void part_two();
    void test();
};