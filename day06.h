#pragma once

#include "common.h"

#define NB_GENS     80
#define NB_GENS_2   256
#define TIMER       6
#define FRESH_TIMER 8

struct day06 {
    std::unordered_map<int, long> fishes;

    day06();

    void part_one();
    void part_two();

    void update();
};