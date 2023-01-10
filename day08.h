#pragma once

#include "common.h"

using strvec = std::vector<std::string>;
using input_line = std::pair<std::vector<std::string>, std::vector<std::string>>;

bool contains(std::string s1, std::string s2) { for (auto& c : s2) { if (s1.find(c) == std::string::npos) return false;} return true;}


int unique_seglengths[4] = {2, 3, 4, 7};
bool in_unique(std::string s) {return std::find(std::begin(unique_seglengths), std::end(unique_seglengths), s.length()) != std::end(unique_seglengths);};

struct entry {
    std::string itos_map[10];
    std::map<std::string, int> stoi_map;
    input_line line;

    std::vector<std::function<bool(std::string, std::string[])>> predicate_vect {
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 6 && !(contains(s, itos_map[4]) && contains(s, itos_map[1])) && itos_map[4].compare("init") != 0);},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 2);},
    [](const std::string& s, const std::string itos_map[10]) {return false;},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 5) && (contains(s, itos_map[1]));},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 4);},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 5 && contains(itos_map[9], s) && !contains(s, itos_map[1]) && itos_map[1].compare("init") != 0);},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 6 && !contains(s, itos_map[1]) && itos_map[1].compare("init") != 0);},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 3);},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 7);},
    [](const std::string& s, const std::string itos_map[10]) {return (s.length() == 6 && contains(s, itos_map[4]));}
    };  

    void fill_maps();
    int sum_outputvalues();
    entry();
    entry(input_line ipt_line) : line(ipt_line) {
        for (int i = 0; i < 10; ++i) {
            itos_map[i] = "init";
        }
    };
};

struct day08 {
    std::vector<input_line> input;

    day08();

    void part_one();
    void part_two();
};