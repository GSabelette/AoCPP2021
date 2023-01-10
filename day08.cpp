#include "day08.h"

day08::day08() {
    auto input_str = readFile("inputs/day08.input");
    for (auto& line : input_str) {
        auto first_split = split_string(line, "|");

        auto pair_first = split_string(first_split[0], " ");
        pair_first.pop_back();

        std::for_each(pair_first.begin(), pair_first.end(), [](auto& s){return std::sort(s.begin(), s.end());});
        std::sort(pair_first.begin(), pair_first.end(), [](std::string s1, std::string s2){return s1.size() < s2.size();});

        auto pair_second = split_string(first_split[1], " ");
        pair_second.erase(pair_second.begin());
        std::for_each(pair_second.begin(), pair_second.end(), [](auto& s){return std::sort(s.begin(), s.end());});

        input.push_back(std::pair<strvec, strvec>(pair_first, pair_second));
    }
}

void entry::fill_maps() {
    // We can determine all numbers in two loops assuming they're ordered by word length
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < predicate_vect.size(); i++) {
            for (const auto& str_number : line.first) {
                if (predicate_vect[i](str_number, itos_map)) {
                    stoi_map[str_number] = i;
                    itos_map[i] = str_number;
                }
            }
        }
    }
    // Special case for 2.
    for (const auto& str_number : line.first) {
        if (str_number.length() == 5 && !stoi_map.contains(str_number)) {
            stoi_map[str_number] = 2;
            itos_map[2] = str_number;
        }
    }
}

int entry::sum_outputvalues() {
    int sum = 0;
    for (int i = 0; i < line.second.size(); i++) 
        sum += (pow(10, line.second.size() - i - 1) * stoi_map[line.second[i]]);
    return sum;
}

void day08::part_one() {
    int count = 0;
    for (auto& line : input) {
        for (auto& output_value : line.second) {
            if (in_unique(output_value)) count++;
        }
    }
    std::cout << "Part one answer : " << count << "\n";
}

void day08::part_two() {
    std::vector<entry> entries;
    for (const auto& entry_line : input) {
        entries.emplace_back(entry(entry_line));
    }
    int total_sum = 0;
    for (auto& entry : entries) {
        entry.fill_maps();
        total_sum += entry.sum_outputvalues();
    }
    std::cout << "Part two answer : " << total_sum << "\n";
}

int main(int argc, const char** argv) {
    day08 day08;
    day08.part_one();
    day08.part_two();
}