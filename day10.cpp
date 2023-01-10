#include "day10.h"

day10::day10() {
    input = readFile("inputs/day10.input");
}

void day10::part_one() {
    int count = 0;
    opening_characters.insert(input[0].back());
    for (const auto& line : input) {
        std::vector<char> lifo_vec;
        for (const auto& c : line) {
            if (opening_characters.find(c) != opening_characters.end()) lifo_vec.push_back(c);
            else {
                if (match_map[lifo_vec.back()] != c) {
                    corrupted_lines.insert(line);
                    count += score_map[c];
                    break;
                }
                else lifo_vec.pop_back();
            }
        }
    }
    std::cout << "Part one answer : " << count << "\n";
}

void day10::part_two() {
    std::vector<uint64_t> scores;
    for (const auto& line : input) {
        if (corrupted_lines.find(line) == corrupted_lines.end()) {
            std::vector<char> lifo_vec;
            for (const auto& c : line) {
                if (opening_characters.find(c) != opening_characters.end()) lifo_vec.push_back(c);
                else lifo_vec.pop_back();
            }
            uint64_t score = 0;
            while (!lifo_vec.empty()) {
                auto cur_char = lifo_vec.back();
                lifo_vec.pop_back();
                score = (score * 5) + part_two_score_map[cur_char];
            }   
            scores.push_back(score);
        }
    }
    std::sort(scores.begin(), scores.end());
    std::cout << "Part two answer : " << scores[scores.size()/2] << "\n";
}
    
// Part two is dependant from part one since it relies on it to recognize corrupted lines
int main(int argc, const char** argv) {
    day10 day10;
    day10.part_one();
    day10.part_two();
}
