#include "day14.h"

#define PART_ONE_STEPS 10
#define PART_TWO_STEPS 40

day14::day14() {
    auto input_str = readFile("inputs/day14.input");
    base_string = input_str[0];
    for (auto it = input_str.begin() + 2; it != input_str.end(); it++) {
        auto str = *it;
        rules[std::pair<char,char>(str[0], str[1])]  = str[6];
    }
    for (const auto& keyval : rules) for (uint8_t i = 0; i < base_string.size(); ++i) {
        if (cpair(base_string[i], base_string[i+1]) == keyval.first) pair_freqs[keyval.first]++;
    }
}

void day14::step() {
    std::unordered_map<cpair, long long, PairHash<char,char>> temp;
    for (const auto& keyval : pair_freqs) {
        temp[cpair(keyval.first.first, rules[keyval.first])] += keyval.second;
        temp[cpair(rules[keyval.first], keyval.first.second)] += keyval.second;
    }
    pair_freqs = temp;
}

void day14::part_one() {
    for (int i = 0; i < PART_ONE_STEPS; ++i) step();
    std::unordered_map<char, long long> char_count;
    for (const auto& keyval : pair_freqs) char_count[keyval.first.first] += keyval.second; 
    for (const auto& c : base_string) char_count[c]++; 
    auto [fmin, fmax] = std::ranges::minmax(char_count | std::ranges::views::values);
    std::cout << "Part one answer : " << fmax - fmin << "\n";
}

void day14::part_two() {
    for (int i = PART_ONE_STEPS; i < PART_TWO_STEPS; ++i) step();
    std::unordered_map<char, long long> char_count;
    for (const auto& keyval : pair_freqs) char_count[keyval.first.first] += keyval.second; 
    for (const auto& c : base_string) char_count[c]++; 
    auto [fmin, fmax] = std::ranges::minmax(char_count | std::ranges::views::values);
    std::cout << "Part two answer : " << fmax - fmin << "\n";
}

// Part two doesn't run without part one, or you have to change i to start from 0.
int main(int argc, const char** argv) {
    day14 day14;
   day14.part_one();
   day14.part_two();
}