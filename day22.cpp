#include "day22.h"

Instruction::Instruction(std::string s) {
    auto split = split_string(s, " ");
    on = (split[0].compare("on") == 0) ? 1 : -1;
    split = split_string(split[1], ",");
    auto parse_xyz = [&](std::string& s, range& r) {
        r.first = std::stoi(s.substr(s.find('=')+1, s.find('.')));
        r.second = std::stoi(s.substr(s.find('.')+2));
    };
    for (size_t i = 0; i < split.size(); ++i) parse_xyz(split[i], xyz[i]);
}

day22::day22() {
    auto input = readFile("inputs/day22.input");
    for (auto& s : input) 
        instructions.emplace_back(Instruction(s));
}

bool valid(const shape& s) {
    return std::accumulate(s.begin(), s.end(), 0,
        [](int v, range r){return (v += (r.first > r.second));}) == 0;
}

shape compute_overlap(const shape& s, const shape& other) {
    return shape {{
        {std::max(s[0].first, other[0].first), std::min(s[0].second, other[0].second)},
        {std::max(s[1].first, other[1].first), std::min(s[1].second, other[1].second)},
        {std::max(s[2].first, other[2].first), std::min(s[2].second, other[2].second)}
    }};
}

unsigned long volume(const shape& s) {
    return std::accumulate(s.begin(), s.end(), 1.0, 
    [](unsigned long sum, range r){sum*=(r.second - r.first + 1); return sum;});
}

// Based on the idea that vol(A+B) = vol(A) + vol(B) - vol(overlap(AB)).
void day22::fill(const Instruction& i) {
    std::vector<Instruction> overlapped;
    if (i.on == 1) overlapped.push_back(i);
    for (const auto& other : completed) {
        shape overlapShape = compute_overlap(i.xyz, other.xyz);
        if (valid(overlapShape)) 
            overlapped.push_back(Instruction(-other.on, overlapShape));
    }
    completed.insert(completed.end(), overlapped.begin(), overlapped.end());
}

void day22::part_one() {
    int64_t total_cubes = 0;
    for (const auto& i : instructions) {
        if (std::abs(i.xyz[0].first) > 50) break;
        fill(i);
    }
    for (const auto& i : completed) 
        total_cubes += (i.on * volume(i.xyz));
    std::cout << "Part one : " << total_cubes << "\n";
}

void day22::part_two() {
    completed.clear();
    unsigned long total_cubes = 0;
    for (const auto& i : instructions) 
        fill(i);
    for (const auto& i : completed) 
        total_cubes += (i.on * volume(i.xyz));
    std::cout << "Part two : " << total_cubes << "\n";
}

int main(int argc, char** argv) {
    day22 day22;
    day22.part_one();
    day22.part_two();
}