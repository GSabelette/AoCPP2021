#pragma once

#include "common.h"

using cpair = std::pair<char,char>;

struct day14 {
    std::string base_string;    
    std::unordered_map<cpair, char, PairHash<char,char>> rules;
    std::unordered_map<cpair, long long, PairHash<char,char>> pair_freqs;

    void step();

    day14();

    void part_one();
    void part_two();
};