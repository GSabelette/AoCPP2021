#pragma once

#include "common.h"

using point = std::pair<int,int>;

struct compare {
    bool operator () (const std::pair<point,int>& p1, const std::pair<point,int>& p2) const {
        return p2.second < p1.second;
    }
};

inline const bool in_bounds(int size, const point* p) {return p->first>=0 && p->second>=0 && p->first<size && p->second<size;}

const auto get_neighbours(const point& p) {
    return std::vector<point> {
        point(p.first + 1, p.second),
        point(p.first - 1, p.second),
        point(p.first, p.second + 1),
        point(p.first, p.second - 1)
    };
}

struct day15 {
    std::unordered_map<point, int, PairHash<int,int>> cost_map;
    day15();

    void part_one();
    void part_two();
};
