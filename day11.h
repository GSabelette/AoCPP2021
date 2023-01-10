#pragma once

#include "common.h"

#define MATRIX_SIZE 10
#define THRESHOLD   9

struct day11 {
    std::vector<std::vector<int>> matrix;
    std::vector<std::pair<int,int>> can_flash;
    std::unordered_set<std::pair<int,int>, PairHash<int,int>> flashed;
    int nb_flash = 0;

    day11();

    inline void flash(std::pair<int,int>* p);
    inline void step();
    void checkadd_flash(int i, int j);

    void part_one();
    void part_two();
};
