#include "day04.h"

day04::day04() {
    auto input_str = readFile("inputs/day04.input");
    winning_numbers = split_string<int>(input_str[0], ",", [](std::string s) {return stoi(s);});
    input_str.erase(input_str.begin());
    int i = 0;
    std::string cur_string;
    for (auto& str : input_str) {
        if (str.compare("") == 0) {
            grids.emplace_back(Grid(cur_string));
            cur_string.clear();
            ++i;
        }
        else {
            cur_string.append(str);
            cur_string.append(" ");
        }
    }
    grids.emplace_back(Grid(cur_string));
}

Grid::Grid(const std::string s) {
    std::vector<int> grid_ints = split_string<int>(s, " ", [](std::string s) {return stoi(s);});
    for (int index = 0; index < BITSET_SIZE; index++) pos_map[grid_ints[index]] = index;
}

bool Grid::update_and_check(const int x) {
    if (auto it = pos_map.find(x); it != pos_map.end()) {
        const int index = it->second;
        pos_map.erase(it);
        marks.set(BITSET_SIZE - 1 - index);
        auto horizontal_candidate = horizontal_winning_marks[index / 5];
        auto vertical_candidate = vertical_winning_marks[index % 5];
        return ((marks & horizontal_candidate) == horizontal_candidate || (marks & vertical_candidate) == vertical_candidate);
    }
    return false;
}

int Grid::score() {
    return std::accumulate(pos_map.begin(), pos_map.end(), 0, 
                            [](int sum, const auto& keyval) {return sum + keyval.first;});
}

void day04::part_one() {
    for (auto& winning_number : winning_numbers) {
        for (auto& grid : grids) {
            if (grid.update_and_check(winning_number)) {
                std::cout << "Part one answer : " << grid.score() * winning_number << "\n";
                return;
            }
        }
    } 
}

void day04::part_two() {
    for (auto& winning_number : winning_numbers) {
        for (auto grid = grids.begin(); grid != grids.end();) {
            if (grid->update_and_check(winning_number)) {
                if (grids.size() != 1) {
                    grids.erase(grid);
                }
                else {
                    std::cout << "Part two answer : " << grid->score() * winning_number << "\n";
                    return;
                }
            }
            else {
                grid++;
            }
        }
    }
}

int main(int argc, const char** argv) {
    day04 day04;
    //day04.part_one();
    day04.part_two();
}