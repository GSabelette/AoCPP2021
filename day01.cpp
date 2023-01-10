#include "day01.h"

day01::day01() {
    auto input_str = readFile("inputs/day01.input");
    input = std::vector<int>(input_str.size());
    std::transform(input_str.begin(), input_str.end(), input.begin(),
                    [](const std::string& string) { 
                        return static_cast<int>(fast_atol(string.c_str()));
                    });
}

void day01::part_one() {
    int result = 0;
    for (int i = 0; i < input.size() - 1; i++) {
        if (input[i] < input[i+1]) result++;
    }
    std::cout << "Part one result : " << result << "\n";
}

void day01::part_two() {
    int result = 0;
    for(auto i: std::ranges::views::iota(3u, input.size())) {
        auto first = input[i-1] + input[i-2] + input[i-3];
        auto second = input[i] + input[i-1] + input[i-2];
        result += second - first > 0;
    }
    std::cout << "Part two result : " << result << "\n";
}

int main(int argc, char** argv) {
    day01 day01{};
    day01.part_one();
    day01.part_two();
}