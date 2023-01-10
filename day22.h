#pragma once

#include "common.h"

using range = std::pair<int, int>;
using shape = std::array<range, 3>;

struct Instruction {
    int on;
    shape xyz;
    Instruction(std::string s);
    Instruction(int o, shape s) : on(o), xyz(s) {}
};

struct day22 {
    std::vector<Instruction> instructions;
    std::vector<Instruction> completed;

    int64_t executeInstruction(const Instruction& i);
    void fill(const Instruction& i);

    day22();
    void part_one();
    void part_two();
};