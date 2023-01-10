#include "day11.h"

#define NB_STEPS 100

day11::day11() {
    auto input_str = readFile("inputs/day11.input");
    for (const auto& line : input_str) {
        std::vector<int> v;
        for (const auto& c : line) v.push_back(c - '0');
        matrix.push_back(v);
    }
}

inline void day11::flash(std::pair<int,int>* p) {
    int i = p->first;
    int j = p->second;
    flashed.insert(std::pair<int,int>(i,j));
    for (int k = i-1; k < i+2; k++) {
        for (int t = j-1; t < j+2; t++) {
            if (k > -1 && k < MATRIX_SIZE && t > -1 && t < MATRIX_SIZE) {
                matrix[k][t]++;
                checkadd_flash(k,t);
            }
        }
    }
}

void day11::checkadd_flash(int i, int j) {
    if (matrix[i][j] > THRESHOLD && flashed.find(std::pair<int,int>(i,j)) == flashed.end()) {
        can_flash.emplace_back(std::pair<int,int>(i,j));
        flashed.insert(std::pair<int,int>(i,j));
    }
}

inline void day11::step() {
    std::for_each(matrix.begin(), matrix.end(), [](auto& v) {
        std::for_each(v.begin(), v.end(), [](auto& i) {
            i++;
        });
    });
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            checkadd_flash(i,j);
        }
    }
    while (!can_flash.empty()) {
        auto p = can_flash.back();
        can_flash.pop_back();
        flash(&p);
        ++nb_flash;
    }
    for (const auto& p : flashed) {
        matrix[p.first][p.second] = 0;
    }
}

void day11::part_one() {
    for (int s = 0; s < NB_STEPS; ++s){
        step();
        can_flash.clear();
        flashed.clear();
    }
    std::cout << "Part one answer : " << nb_flash << "\n";
}

void day11::part_two() {
    int count = 0;
    while (true) {
        step();
        count++;
        if (flashed.size() == 100) break;
        can_flash.clear();
        flashed.clear();
    }
    std::cout << "Part two answer : " << count << "\n";
}

// You can only execute one part at a time due to how the values are stored in the struct
int main(int argc, char** argv) {
    day11 day11;
    //day11.part_one();
    day11.part_two();
}
