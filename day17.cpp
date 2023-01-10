#include "day17.h"

day17::day17() {
    auto input_str = readFile("inputs/day17.input")[0];
    auto split_str = split_string(input_str, ",");
    xmin = std::stoi(split_str[0].substr(split_str[0].find('=')+1, split_str[0].find('.') - split_str[0].find('=')+1));
    xmax = std::stoi(split_str[0].substr(split_str[0].find('.')+2));
    ymin = std::stoi(split_str[1].substr(split_str[1].find('=')+1, split_str[1].find('.') - split_str[1].find('=')+1));
    ymax = std::stoi(split_str[1].substr(split_str[1].find('.')+2));
}

//This is stupid. Don't do this.
void day17::part_one() {
    int y;
    for (int i = 0; i < 10000 ; ++i) {
        int maxi = arithmetic_sum(i);
        for (int n = i; n < i + 100; ++n)
            if (in_ybounds(maxi - arithmetic_sum(n))) {
                y = i;
                break;
            }
    }
    upper_y = y;
    std::cout << "Part one answer is : " << arithmetic_sum(y) << "\n";
}

//This is stupid too.
void day17::part_two() {
    std::map<int, std::set<int>> x_steps_map;
    std::map<int, std::set<int>> y_steps_map; 

    for (int v0 = ymin; v0 <= upper_y; v0++) {
        if (v0 <= 0) {
            int traj_y = 0;
            int step = 0;
            while (traj_y >= ymin) {
                traj_y += v0 - step;
                step++;
                if (in_ybounds(traj_y)) y_steps_map[step].insert(v0);
            }
        }
        else {
            int maxi = arithmetic_sum(v0);
            for (int step = 0; step <= upper_y + 10; step++) {
                if (in_ybounds(maxi - arithmetic_sum(step))) y_steps_map[step + v0 + 1].insert(v0);
            }
        }
    }
    for (int v0 = 1 ; v0 <= xmax; v0++) {
        int traj_x = 0;
        auto max_step = std::ranges::max(y_steps_map | std::views::keys);
        for (int step = 0; step <= max_step; step++) {
            traj_x += std::max(v0 - step, 0);
            if (in_xbounds(traj_x)) x_steps_map[step + 1].insert(v0);
        }
    }

    int tot_trajectories = 0;
    std::unordered_set<std::pair<int,int>, PairHash<int,int>> seen;
    for (const auto& key : x_steps_map | std::views::keys) {
        for (const auto& xval : x_steps_map[key]) {
            for (const auto& yval: y_steps_map[key]) {
                if (!seen.count(std::pair<int, int>(xval,yval))) {
                    tot_trajectories++;
                    seen.insert(std::pair<int,int>(xval,yval));
                }
            }
        }
    }
    std::cout << "Part two answer : " << tot_trajectories << "\n";
}

//This is so stupid part two won't run without part one.
int main(int argc, const char** argv) {
    day17 day17;
    day17.part_one();
    day17.part_two();
}