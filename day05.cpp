#include "day05.h"

day05::day05() {
    auto input_str = readFile("inputs/day05.input");
    input.reserve(input_str.size());
    for (auto& str : input_str) input.emplace_back(Line(str));
}

void day05::part_one() {
    for (auto& line : input) {
        if (line.is_horizontal()) {
            int y = line.first_point.coordY;
            for (int x = std::min(line.first_point.coordX, line.second_point.coordX); x < (std::max(line.first_point.coordX, line.second_point.coordX) + 1); x++) {
                map[std::pair<int,int>(x,y)]++; 
            }
        }
        if (line.is_vertical()) {
            int x = line.first_point.coordX;
            for (int y = std::min(line.first_point.coordY, line.second_point.coordY); y < (std::max(line.first_point.coordY, line.second_point.coordY) + 1); y++) {
                map[std::pair<int,int>(x,y)]++; 
            }
        }
    }
    int count = 0;
    std::unordered_map<std::pair<int, int>, int, PairHash<int,int>>::iterator it;
    for (it = map.begin(); it != map.end(); it++) {
        if (it->second >= 2) count++;
    }
    std::cout << "Part one answer : " << count << "\n";
}

void day05::part_two() {
    for (auto& line : input) {
        if (line.is_horizontal()) {
            int y = line.first_point.coordY;
            for (int x = std::min(line.first_point.coordX, line.second_point.coordX); x < (std::max(line.first_point.coordX, line.second_point.coordX) + 1); x++) {
                map[std::pair<int,int>(x,y)]++; 
            }
        } else if (line.is_vertical()) {
            int x = line.first_point.coordX;
            for (int y = std::min(line.first_point.coordY, line.second_point.coordY); y < (std::max(line.first_point.coordY, line.second_point.coordY) + 1); y++) {
                map[std::pair<int,int>(x,y)]++; 
            }
        } else {
            int ax = ((line.second_point.coordX - line.first_point.coordX) > 0) ? 1 : -1;
            int ay = ((line.second_point.coordY - line.first_point.coordY) > 0) ? 1 : -1;
            for (int k = 0; k < std::abs(line.first_point.coordX - line.second_point.coordX) + 1; k++) {
                map[std::pair<int,int>(line.first_point.coordX + ax * k, line.first_point.coordY + ay * k)]++;
            }
        }
    }
    int count = 0;
    std::unordered_map<std::pair<int, int>, int, PairHash<int,int>>::iterator it;
    for (it = map.begin(); it != map.end(); it++) {
        if (it->second >= 2) count++;
    }
    std::cout << "Part two answer : " << count << "\n";
}

Point::Point(std::string s) {
    coordX = std::stoi(s.substr(0, s.find(",")));
    coordY = std::stoi(s.substr(s.find(",") + 1, s.size() - 1));
}

Line::Line(std::string s) {
    first_point = Point(s.substr(0, s.find(" ")));
    second_point = Point(s.substr(s.find(">") + 2, s.size() - 1));
}

int main(int argc, const char** argv) {
    day05 day05;
    if (argc != 2) {
        std::cout << "Expected what part you wanted to solve\n";
        return -1;
    }
    int part = std::stoi(argv[1]);
    if (part == 1) day05.part_one();
    else day05.part_two();
}