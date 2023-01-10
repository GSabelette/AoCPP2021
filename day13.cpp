#include "day13.h"

#define FOLD_CHAR_POS 11

day13::day13() {
    auto input_str = readFile("inputs/day13.input");
    bool fold_lines = false;
    for (const auto& line : input_str) {
        if (!fold_lines) {
            if (!line.empty()) {
                points.emplace_back(std::pair<int,int>(std::stoi(line.substr(0, line.find(","))),std::stoi(line.substr(line.find(",")+1))));       
            }
            else fold_lines = true;
        }
        else {
            fold_instructions.emplace_back(std::pair<char, int>(line[FOLD_CHAR_POS], std::stoi(line.substr(line.find("=") + 1))));
        }
    }
}

void fold(int& n, int f) {n = f - std::abs(n - f);}

auto fold_axis(auto& folding_instruction) {
    return [=](auto& p) {
        fold((folding_instruction.first == 'x') ? p.first : p.second, folding_instruction.second);
        return p;
    };
} 

void fold_all(auto& points, auto& folding_instructions) {
    for (const auto& f : folding_instructions) 
        std::ranges::transform(points.begin(), points.end(), points.begin(), fold_axis(f));
    std::sort(points.begin(), points.end() );
    points.erase(unique(points.begin(), points.end()), points.end());
}

void fold_one(auto& points, auto& folding_instructions) {
    std::ranges::transform(points.begin(), points.end(), points.begin(), fold_axis(folding_instructions));    
    std::sort(points.begin(), points.end() );
    points.erase(unique(points.begin(), points.end()), points.end());
}

void day13::part_one() {
    fold_one(points, fold_instructions[0]);
    std::cout << "Part one answer : " << points.size() << "\n";
}

void day13::part_two() {
    fold_all(points, fold_instructions);
    auto [xmin, xmax] = std::ranges::minmax(points | std::ranges::views::keys);
    auto [ymin, ymax] = std::ranges::minmax(points | std::ranges::views::values);

    auto height = xmax - xmin + 1, width = ymax - ymin + 1;
    std::vector<std::vector<char>> paper(width);
    for (auto& v : paper) v.resize(height);
    for(const auto& [x,y]: points)
        paper[y-ymin][x-xmin] = '#';

	std::cout << "Part two answer : " << '\n';
	for (const auto& v : paper) {
        for (const char c : v) if (c != '#') std::cout << " "; else std::cout << c;
        std::cout << "\n";
    }
}

int main(int argc, const char** argv) {
    day13 day13;
    //day13.part_one();
    day13.part_two();
}