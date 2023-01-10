#include "day07.h"

day07::day07() {
    auto input_str = readFile("inputs/day07.input");
    positions = split_string<int>(input_str[0], ",", [](const std::string s) {return std::stoi(s);} );
    std::sort(positions.begin(), positions.end());
}

void day07::part_one() {
    auto median = (positions[(positions.size()/2) - 1] + positions[positions.size()/2]) / 2.0;
    int sum = 0;
    for (auto& it : positions) sum+=std::abs(it - median);
    std::cout << "Part one answer : " << sum << "\n";
}

void day07::part_two() {
    auto median = std::floor((std::reduce(positions.begin(), positions.end()) / static_cast<float>(positions.size())) - 0.5);
    std::cout << "Part two median is : " << median << "\n";
    int sum = 0;
    for (auto& it : positions) {
        int n = std::abs(it - median);
        sum += n*(n+1)/2.0;
    }
    std::cout << "Part one answer : " << sum << "\n";
}
 
int main(int argc, const char** argv) {
    day07 day07;
    day07.part_one();
    day07.part_two();
}