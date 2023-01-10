#pragma once

#include "common.h"

int arithmetic_sum(int n) {return (n*(n+1)/2);}

struct day17 {
    int xmin, xmax;
    int ymin, ymax;
    int upper_y;

    bool in_xbounds(int x) {return xmin <= x && x <= xmax;}
    bool in_ybounds(int y) {return ymin <= y && y <= ymax;}

    day17();

    void part_one();
    void part_two();
};