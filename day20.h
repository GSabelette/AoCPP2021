#pragma once

#include "common.h"

using board = std::vector<std::vector<int>>;

struct day20 {
    std::string algorithm;
    board image;
    board image_next;

    void apply_algo();
    int at(int i, int j);

    day20();

    void part_one();
    void part_two();
};