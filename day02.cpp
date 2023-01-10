#include "day02.h"

day02::day02() {
    auto input_str = readFile("inputs/day02.input");
    input = std::unordered_map<std::string, int> { {"forward", 0}, {"down", 0}, {"up", 0} };
    std::for_each(input_str.begin(), input_str.end(), 
                    [&](const std::string& string) {
                        input[string.substr(0, string.find(" "))] += std::stoi(string.substr(string.find_last_not_of("0123456789") + 1));
                    });
}

void day02::part_one() {
    depth = input["down"] - input["up"];
    forwardPos = input["forward"];
    std::cout << "Part one answer : " << depth * forwardPos << "\n";
}

void day02::part_two() {
    depth = 0;
    forwardPos = 0;
    auto input_str = readFile("inputs/day02.input");
    std::for_each(input_str.begin(), input_str.end(), 
                [&](const std::string& string) {
                    std::string str_token = string.substr(0, string.find(" "));
                    int int_token = stoi(string.substr(string.find_last_not_of("0123456789") + 1));
                    if (str_token.compare("forward") == 0) {
                        forwardPos += int_token;
                        depth += (int_token*aim);
                    }
                    else if (str_token.compare("up") == 0) {
                        aim -= int_token;
                    }
                    else {
                        aim += int_token;
                    }
                });
    std::cout << "Part two result : " << depth * forwardPos << "\n";
}

int main(int argc, const char** argv) {
    day02 day02{};
    day02.part_one();
    day02.part_two();
}