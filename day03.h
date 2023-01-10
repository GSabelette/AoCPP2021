#pragma once

#include "common.h"

template <int n>
struct day03 {    
    std::vector<std::string> input_str;
    std::vector<std::bitset<n>> columns;

    day03();

    void part_one();
    void part_two();

    int get_rating(int rating_bit);
};