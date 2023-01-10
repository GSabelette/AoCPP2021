#pragma once

#include "common.h"
#define BITSET_SIZE 25
#define NB_GRIDS 100

struct Grid {
    std::unordered_map<int, int> pos_map;
    std::bitset<BITSET_SIZE> marks;

    Grid(const std::string s);

    bool update_and_check(const int x);
    int score();
};

std::ostream& operator<<(std::ostream& os, Grid g) {
    os << "grid { ";
    for(auto it = g.pos_map.cbegin(); it != g.pos_map.cend(); ++it)
    {
        os << it->first << " ";
    }
    os << "}";
    return os;
}

struct day04 {
    std::vector<int> winning_numbers;
    std::vector<Grid> grids;

    day04();

    void part_one();
    void part_two();
};

const std::array<std::bitset<25>, 5> horizontal_winning_marks = {
    std::bitset<25>("1111100000000000000000000"),
    std::bitset<25>("0000011111000000000000000"),
    std::bitset<25>("0000000000111110000000000"),
    std::bitset<25>("0000000000000001111100000"),
    std::bitset<25>("0000000000000000000011111"),
};
const std::array<std::bitset<25>, 5> vertical_winning_marks = {
    std::bitset<25>("1000010000100001000010000"),
    std::bitset<25>("0100001000010000100001000"),
    std::bitset<25>("0010000100001000010000100"),
    std::bitset<25>("0001000010000100001000010"),
    std::bitset<25>("0000100001000010000100001")
};