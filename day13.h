#pragma once

#include "common.h"

struct day13 {
    std::vector<std::pair<int, int>> points;
    std::vector<std::pair<char, int>> fold_instructions;

    day13();

    void part_one();
    void part_two();
};