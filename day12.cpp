#include "day12.h"

day12::day12() {
    auto input_str = readFile("inputs/day12.input");
    for (auto& line : input_str) {
        std::vector<std::string> v = split_string(line, "-");
        graph[v.front()].push_back(v.back());
        graph[v.back()].push_back(v.front());
    }
}

void day12::explore(std::string path, std::string cur, std::unordered_set<std::string> explored) {
    path.append(cur);
    if (cur == "end") {completed_paths.insert(path); return;}
    if (islower(cur[0])) explored.insert(cur);
    for (const auto& adj : graph.at(cur)) {
        if (explored.find(adj) == explored.end()) explore(path, adj, explored);   
    }
}

void day12::explore_two(std::string path, std::string cur, std::unordered_set<std::string> explored, bool revisit) {
    path.append(cur);
    if (cur == "end") {completed_paths.insert(path); return;}
    if (islower(cur[0])) explored.insert(cur);
    for (const auto& adj : graph.at(cur)) {
        if (explored.find(adj) == explored.end())       explore_two(path, adj, explored, revisit);    
        else if (!revisit && adj != "start") explore_two(path, adj, explored, true);
    }
}

void day12::part_one() {
    std::unordered_set<std::string> explored;
    explore(std::string{}, "start", explored);
    std::cout << "Part one answer : " << completed_paths.size() << "\n"; 
}

void day12::part_two() {
    std::unordered_set<std::string> explored;
    explore_two(std::string{}, "start", explored, false);
    std::cout << "Part two answer : " << completed_paths.size() << "\n";
}
// Parts must be launched one at a time
int main(int argc, const char** argv) {
    day12 day12;
    //day12.part_one();
    day12.part_two();
}