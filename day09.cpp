#include "day09.h"

day09::day09() {
    auto input_str = readFile("inputs/day09.input");
    for (const auto& line : input_str) {
        std::vector<int> v;
        for (const auto& c : line) v.push_back(c - '0');
        matrix.push_back(v);
    }
    
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) 
            if (is_low_point(i, j)) low_points[std::pair<int,int>(i,j)] = matrix[i][j];
    }
}

bool day09::is_low_point(int i, int j) {
    bool b = true;
    int cur_point = matrix[i][j]; 
    if (i != 0)                 b &= (cur_point < matrix[i-1][j]);
    if (i != MATRIX_SIZE - 1)   b &= (cur_point < matrix[i+1][j]);
    if (j != 0)                 b &= (cur_point < matrix[i][j-1]);
    if (j != MATRIX_SIZE - 1)   b &= (cur_point < matrix[i][j+1]);
    return b;
}

std::set<std::pair<int,int>> day09::get_adj_points(int i, int j) {
    std::set<std::pair<int,int>> s;
    if (i != 0)                 if(matrix[i-1][j] != HIGHEST) s.insert(std::pair<int,int>(i-1, j));
    if (i != MATRIX_SIZE - 1)   if(matrix[i+1][j] != HIGHEST) s.insert(std::pair<int,int>(i+1, j));
    if (j != 0)                 if(matrix[i][j-1] != HIGHEST) s.insert(std::pair<int,int>(i, j-1));
    if (j != MATRIX_SIZE - 1)   if(matrix[i][j+1] != HIGHEST) s.insert(std::pair<int,int>(i, j+1));
    return s;
}

void day09::part_one() {
    int count = std::accumulate(low_points.cbegin(), low_points.cend(), 0, 
                [](int count, const auto& entry){return count + entry.second + 1;});
    std::cout << "Part one answer : " << count << "\n";
}

void day09::part_two() {
    std::vector<int> basin_sizes;
    for (const auto& low_point : low_points) {
        std::vector<std::pair<int,int>> cur_points;
        int basin_size = 0;
        cur_points.push_back(low_point.first);
        seen_points.insert(low_point.first);
        while(!cur_points.empty()) {
            std::pair<int,int> cur_point = cur_points.back(); 
            cur_points.pop_back();
            
            // Get points adjacent to cur_point and add them to points to be treated if they were not already seen.
            auto s = get_adj_points(cur_point.first, cur_point.second);
            for (const auto& p : s) {
                if (seen_points.find(p) == seen_points.end()) cur_points.push_back(p);
            }
            std::merge(s.begin(), s.end(), seen_points.begin(), seen_points.end(), std::inserter(seen_points, seen_points.begin()));   
            ++basin_size;
        }
        basin_sizes.push_back(basin_size);
    }
    std::sort(basin_sizes.begin(), basin_sizes.end(), [](int i, int j) {return i > j;});
    int count = std::accumulate(basin_sizes.begin(), basin_sizes.begin()+3, 1, std::multiplies<int>());
    std::cout << "Part two answer : " << count << "\n";
}

int main(int argc, const char** argv) {
    day09 day09;
    day09.part_one();
    day09.part_two();
}