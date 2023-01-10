#pragma once 

#include "common.h"

#define MATRIX_SIZE 100
#define HIGHEST 9

struct day09 {
    std::vector<std::vector<int>> matrix;
    std::unordered_map<std::pair<int,int>, int, PairHash<int,int>> low_points;
    std::set<std::pair<int,int>> seen_points;

    bool is_low_point(int i, int j);
    std::set<std::pair<int,int>> get_adj_points(int i, int j);

    day09();

    void part_one();
    void part_two();
};