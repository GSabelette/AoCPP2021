#include "day06.h"

day06::day06() {
    auto input_str = readFile("inputs/day06.input");
    auto v = split_string<long>(input_str[0], ",", [](std::string s) {return std::stol(s);});
    for (long i = 1; i < TIMER; i++) fishes[i] = std::count(v.begin(), v.end(), i); 
}

void day06::update() {
    long nb_zeros = fishes[0];
    for (int i = 0; i < FRESH_TIMER; i++) {
        fishes[i] = fishes[i+1];
    }
    fishes[8] = nb_zeros;
    fishes[6] += nb_zeros; 
}

void day06::part_one() {
    for (int i = 0; i < NB_GENS; i++) update();
    long sum = 0;
    for (int i = 0; i < FRESH_TIMER + 1; i++) sum+=fishes[i];
    std::cout << "Part one answer : " << sum << "\n";
}

void day06::part_two() {
    for (int i = 0; i < NB_GENS_2; i++) update();
    long sum = 0;
    for (int i = 0; i < FRESH_TIMER + 1; i++) sum+=fishes[i];
    std::cout << "Part two answer : " << sum << "\n";
}

int main(int argc, const char** argv) {
    day06 day06;
    //day06.part_one();
    day06.part_two();
}