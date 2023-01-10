#include "day21.h"

#define BOARD_SIZE 10

#define PART_ONE_SCORE 1000
#define PART_TWO_SCORE 21

#define D100 100
#define D3 3

day21::day21() {
    auto input = readFile("inputs/day21.input");
    pos1 = input[0].back() - '0';
    pos2 = input[1].back() - '0';
}

void day21::part_one() {
    Player p1(pos1);
    Player p2(pos2);

    int nb_rolls = 0;

    auto roll = [&]() {
        ++nb_rolls;
        ++diceValue;
        if (diceValue > D100) diceValue -= D100; 
        return diceValue;
    };
    auto play = [&](Player& p) {
        int16_t move = roll() + roll() + roll();
        move %= BOARD_SIZE;
        p.pos += move;
        if (p.pos > BOARD_SIZE) p.pos -= BOARD_SIZE;
        p.score += p.pos;
    };
    while (p1.score < PART_ONE_SCORE && p2.score < PART_ONE_SCORE) {
        play(p1);
        if (p1.score >= PART_ONE_SCORE) {
            break;
        }
        play(p2);
    }
    std::cout << "Part one : " << nb_rolls * std::min(p1.score, p2.score) << "\n";
}

void day21::part_two() {
    std::array<std::pair<int, int>, 7> rollPossibilities {{{3,1}, {4,3}, {5,6}, {6,7}, {7,6}, {8,3}, {9,1}}};

    int64_t wins[2] {0,0};

    std::deque<Universe> universes;
    universes.emplace_back(Universe(Player(pos1), Player(pos2)));

    auto play = [&](Player& p, int roll) {
        p.pos += roll;
        if (p.pos > BOARD_SIZE) p.pos -= BOARD_SIZE;
        p.score += p.pos;
    };

    auto turn = [&](Universe& u, int roll) {
        play(u.p[u.curPlayer], roll);
        if (u.p[u.curPlayer].score >= 21)
            wins[u.curPlayer] += u.count;
        else {
            u.curPlayer = 1 - u.curPlayer;
            universes.push_back(u);
        }
    };

    auto step = [&](Universe& u) {
        for (const auto& poss : rollPossibilities) {
            Universe newUniverse = u;
            newUniverse.count *= poss.second;
            turn(newUniverse, poss.first);
        }
    };

    while (!universes.empty()) {
        step(universes.front());
        universes.pop_front();
    }

    std::cout << "Part two : p1Wins : " << wins[0] << " | p2Wins : " << wins[1] << "\n";
}


int main(int argc, char** argv) {
    day21 day21;
    day21.part_one();
    day21.part_two();
}