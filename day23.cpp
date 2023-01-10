#include "day23.h"

Plan final_state() {
    Plan p;
    p.hallway.fill('.');
    for (size_t i = 0; i < NB_ROOMS; ++i) {
        p.hallway[HALLWAY_SIZE + i] = 'A' + i;
        p.hallway[HALLWAY_SIZE + NB_ROOMS + i] = 'A' + i;
    };
    return p;
}

day23::day23() {
    auto input = readFile("inputs/day23dummy.input");
    p.hallway.fill('.');
    for (size_t i = 0; i < NB_ROOMS; ++i) {
        p.hallway[HALLWAY_SIZE + i] = input[2][3+2*i];
        p.hallway[HALLWAY_SIZE + NB_ROOMS + i] = input[3][3+2*i];
    };
    end = final_state();
}

std::vector<int> Plan::get_alive() const {
    std::vector<int> alive;
    for (size_t i = 0; i < hallway.size(); ++i) if (is_alive(i)) alive.push_back(i);
    return alive;
}

std::vector<int> Plan::adjacences(int p) const {
    std::vector<int> adj {p};
    // Border cases
    switch (p)
    {
    case 0:
        adj.push_back(p+1);
        return adj;
    case 10:
        adj.push_back(p-1);
        return adj;
    default:
        break;
    }
    // First spot in room
    if ((p >= HALLWAY_SIZE) && (p < HALLWAY_SIZE + NB_ROOMS)) {
        adj.push_back(p+NB_ROOMS);
        adj.push_back((p%HALLWAY_SIZE)+2);
        return adj;
    } // Deepest spot in room
    else if ((p >= HALLWAY_SIZE + NB_ROOMS)){
        adj.push_back(p-NB_ROOMS);
        return adj;
    } // Hallway in front of room
    if ((p%2) == 0) {
        adj.push_back((p/2)+HALLWAY_SIZE-1);
    } // Any non-treated Hallway case.
    adj.push_back(p+1);
    adj.push_back(p-1);
    return adj;
}

int depth(int pos) {
    if (pos < 11) return 0;
    else return (pos%11)/4+1;
}

std::vector<int> Plan::moveIn(int pos) const {
    std::vector<int> moves;
    auto possibleDest = destinationsMap[hallway[pos]];
    std::cout << "Possible dest for : " << pos << " | " << possibleDest << "\n";
    int destCol = roomFrontMap[*possibleDest.begin()];
    // If hallway is occupied we don't move in.
    for (int j = std::min(destCol, pos) + 1; j < std::max(destCol, pos); ++j) if (is_alive(j)) return {};
    // If room is occupied by the wrong color we don't move in.
    for (auto& d : possibleDest) if (is_alive(d) && hallway[d] != hallway[pos]) return {};
    // Move to the furthest free spot.
    int dest = *possibleDest.begin();
    for (auto& d : possibleDest) {
        if (!is_alive(d))
            dest = d;
        else break; 
    }
    moves.push_back(dest);
    std::cout << "moveIn : " << pos << " | " << moves << "\n";
    return moves;
}

std::vector<int> Plan::moveOut(int pos) const {
    std::vector<int> moves;
    int destCol = roomFrontMap[*destinationsMap[pos].begin()];
    for (int i = 0; i < HALLWAY_SIZE; ++i) {
        // We can't stop in front of a room.
        if (!frontRooms.contains(i)) {
            bool obstructed = false;
            for (int j = std::min(i, destCol) + 1; j < std::max(i, destCol); ++j) {
                if (is_alive(j)) {
                    obstructed = true;
                    break;
                }
            }
            if (!obstructed) moves.push_back(i);
        }
    }
    return moves;
}

void Plan::swap_places(int i, int j) {
    auto tmp = hallway[i];
    hallway[i] = hallway[j];
    hallway[j] = tmp;
}

using costPair = std::pair<Plan, int>;

// Plans are compared with their associated costs.
struct planCompare {
    bool operator() (const std::pair<Plan,int>& p1, const std::pair<Plan,int>& p2) const {
        return p2.second < p1.second;
    }
};

void day23::explore() {
    std::priority_queue<costPair, std::vector<costPair>, planCompare> pqueue;
    std::unordered_set<Plan, Plan> seen;
    pqueue.emplace(costPair(p, 0));
    while (!pqueue.empty()) {
        auto [p, cost] = pqueue.top();
        pqueue.pop();
        if (p == end) {
            std::cout << "Cost : " << cost << "\n";
            return;
        }
        auto alive = p.get_alive();
        for (const auto& point : alive) {
            std::vector<int> moves;
            if (inRoom(point)) 
                moves = p.moveOut(point);
            else
                moves = p.moveIn(point);

            if (moves == std::vector{0}) std::cout << "Move 0 for point : " << point <<"\n";
            // std::cout << "Point : " << point << " | " << p.hallway[point] << "\n";   
            // std::cout << "Moves : " << moves << "\n";
            for (const auto& move : moves) {
                // std::cout << "Move : " << move << " is alive : " << p.is_alive(move) << "\n";
                if (!p.is_alive(move)) {
                    p.swap_places(move, point);
                    if (seen.contains(p)) {
                        p.swap_places(move, point);
                        continue;
                    }
                    seen.insert(p);
                    int min = std::min(point,move);
                    int max = std::max(point,move);
                    std::cout << "Max : " << max << " | division : " << (max%11)/4 << "\n";
                    int newCost = cost + costsMap[p.hallway[move]] * (std::abs(min - roomFrontMap[max]) + ((max%11)/4));
                    
                    if (p == end) 
                        std::cout << "Cost : " << newCost << "\n";
                    
                    pqueue.push({p, newCost});
                    p.swap_places(move, point);
                }
            }
        }
    }
}

void day23::part_one() {
    explore();
}

int main(int argc, char** argv) {
    day23 day23;
    std::cout << "Final : " << final_state().hallway << "\n";
    auto moves = day23.p.moveOut(11);
    for (const auto& move : moves) {
        day23.p.swap_places(11, move);
        std::cout << "Moved out : " << day23.p.hallway << "\n";
        auto m = day23.p.moveIn(move);
        std::cout << "Move in : " << m << "\n";
        day23.p.swap_places(m[0], move);
        std::cout << "Hallway : " << day23.p.hallway << "\n\n";
        day23.p.swap_places(11, move);
    }

    //day23.part_one();

}