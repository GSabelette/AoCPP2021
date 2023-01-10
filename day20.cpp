#include "day20.h"

#define PART_ONE_GENERATIONS 2
#define PART_TWO_GENERATIONS 50

static int outsideCells = 0;

day20::day20() {
    auto input = readFile("inputs/day20.input");
    algorithm = input[0];
    for (auto&& it = std::next(input.begin(), 2); it != input.end(); ++it) {
        std::vector<int> curLine;
        for (auto&& c : *it) {
            if (c == '#') curLine.push_back(1);
            else curLine.push_back(0);
        }
        image.push_back(curLine);
    }
} 

int day20::at(int i, int j) {
    if (i < 0 || i >= image.size() || j < 0 || j >= image.size()) return outsideCells % 2;
    else return image[i][j];
}

void day20::apply_algo() {
    image_next.clear();
    for (int i = -1; i <= (int)image.size(); ++i) {
        std::vector<int> newLine;
        for (int j = -1; j <= (int)image[0].size(); ++j) {
            size_t newVal = 0;
            for (int iShift = -1; iShift <= 1; iShift++) {
                for (int jShift = -1; jShift <= 1; jShift++) {
                    newVal <<= 1;
                    newVal |= at(i + iShift, j + jShift);
                }
            }
            newLine.push_back(algorithm[newVal] == '#');
        }
        image_next.push_back(newLine);
    }
    image = image_next;
    outsideCells += (algorithm[0] == '#');
}

void day20::part_one() {
    for (int i = 0; i < PART_ONE_GENERATIONS; ++i)
        apply_algo();
    
    std::cout << "Part one : " << std::transform_reduce(image.begin(), image.end(), 0, std::plus<>{}, [] (auto &row) {
        return std::count(row.begin(), row.end(), 1);
    }) << "\n";
}

void day20::part_two() {
    for (int i = PART_ONE_GENERATIONS; i < PART_TWO_GENERATIONS; ++i) 
        apply_algo();

    std::cout << "Part two : " << std::transform_reduce(image.begin(), image.end(), 0, std::plus<>{}, [] (auto &row) {
        return std::count(row.begin(), row.end(), 1);
    }) << "\n";
}

int main(int argc, char** argv) {
    day20 day20;
    day20.part_one();
    day20.part_two();
}