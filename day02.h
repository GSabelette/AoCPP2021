#pragma once

#include "common.h"

struct day02 {
    std::unordered_map<std::string, int> input;
    int depth;
    int forwardPos;

    int aim = 0;

    day02();

    void part_one();
    void part_two();
};