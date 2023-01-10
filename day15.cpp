#include "day15.h"

#define SIZE 100
#define NB_MAPS 5

day15::day15() {
    auto input_str = readFile("inputs/day15.input");
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cost_map[point(i,j)] = input_str[i][j] - '0';
        }
    }
}

int dijkstra(point start, point end, const std::unordered_map<point, int, PairHash<int,int>> cost_map, const int size) {
    std::priority_queue<std::pair<point,int>, std::vector<std::pair<point, int>>, compare> pqueue;
    std::vector<std::vector<bool>> seen_points(size, std::vector<bool>(size, false));
    pqueue.emplace(start,0);
    while (!pqueue.empty()) {
        const auto [cur_p, weight] = pqueue.top();
        pqueue.pop();
        if (cur_p == end) {
            return weight;
        }
        for (const auto& neigh : get_neighbours(cur_p)) {
            if (in_bounds(size, &neigh) && !seen_points[neigh.first][neigh.second]) {
                pqueue.emplace(neigh, weight + cost_map.at(neigh));
                seen_points[neigh.first][neigh.second] = true;;
            }
        }
    }
    std::cout << "Error\n";
    return 0;
}

void day15::part_one() {
    std::cout << "Part one answer : " << dijkstra(point(0,0), point(SIZE-1, SIZE-1), cost_map, SIZE) << "\n";
}

inline std::pair<point, int> create_entry(const std::pair<const point, int> keyval, int i, int j) {
    int weight = keyval.second + i + j;
    if (weight > 9) weight -= 9;
    return std::pair<point,int>(point(keyval.first.first + i * SIZE, keyval.first.second + j * SIZE), weight);
}

void day15::part_two() {
    const auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<point, int, PairHash<int,int>> new_cost_map;   
    new_cost_map.insert(cost_map.begin(), cost_map.end());
    std::unordered_map<point,int, PairHash<int,int>> temp_map;
    for (int i = 1; i < NB_MAPS; ++i) {
        for (const auto& keyval : cost_map) {
            temp_map.insert(create_entry(keyval, i, 0));
            temp_map.insert(create_entry(keyval, 0, i));
        }
    }
    new_cost_map.insert(temp_map.begin(), temp_map.end());
    for (int i = 1; i < NB_MAPS; ++i) {
        for (int j = 1; j < NB_MAPS; ++j) {
            std::unordered_map<point, int, PairHash<int,int>> new_map;   
            for(const auto& keyval : cost_map) new_map.insert(create_entry(keyval, i, j));
            new_cost_map.insert(new_map.begin(), new_map.end());
        }
    }
    std::cout << "Part two answer : " << dijkstra(point(0,0), point(SIZE*NB_MAPS-1, SIZE*NB_MAPS-1), new_cost_map, SIZE * NB_MAPS) << "\n";
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Part two took : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}

int main(int argc, const char** argv) {
    day15 day15;
    day15.part_one();
    day15.part_two();
}
