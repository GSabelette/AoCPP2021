#pragma once

#include "common.h"

std::unordered_map<char, char> match_map {{'{', '}'}, {'(', ')'}, {'[', ']'}, {'<', '>'}};
std::unordered_set<char> opening_characters {'{', '(', '[', '<'};
std::unordered_set<char> closing_characters {'}', ')', ']', '>'};

std::unordered_map<char, int> score_map {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
std::unordered_map<char, int> part_two_score_map {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

struct day10 {
    std::vector<std::string> input;
    std::unordered_set<std::string> corrupted_lines;

    day10();

    void part_one();
    void part_two();
};
