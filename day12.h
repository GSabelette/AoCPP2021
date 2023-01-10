#pragma once

#include "common.h"

struct day12 {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_set<std::string> completed_paths;

    void explore(std::string path, std::string cur, std::unordered_set<std::string> explored);
    void explore_two(std::string path, std::string cur, std::unordered_set<std::string> explored, bool revisit);

    day12();

    void part_one();
    void part_two();
};