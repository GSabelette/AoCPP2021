#include "day03.h"

#define NB_COLUMNS 12
#define NB_LINES 1000

template <>
day03<NB_LINES>::day03() {
    input_str = readFile("inputs/day03.input");
    std::vector<std::string> string_vector(NB_COLUMNS);
    std::for_each(input_str.begin(), input_str.end(),
                    [&](const std::string& string) {
                        for(int i = 0; i < NB_COLUMNS; ++i) {
                            string_vector[i].push_back(string[i]);
                        }
                    });
    std::for_each(string_vector.begin(), string_vector.end(),
                    [&](const std::string& bitstring) {
                        columns.emplace_back(std::bitset<NB_LINES> (bitstring));
                    });
}

template <>
void day03<NB_LINES>::part_one() {
    int gamma = 0b0;
    for(auto& column : columns) {
        if (column.count() > (NB_LINES/2)) gamma = ((gamma<<1)|1);
        else gamma = gamma<<1;
    }
    std::cout << "Part one answer : " << gamma * (gamma ^ 0b111111111111) << "\n";
}

template<>
int day03<NB_LINES>::get_rating(int rating_bit) {
    std::vector<int> remaining_indexes {};
    int kept_bit = ((columns[0].count() >= NB_LINES/2.0) == rating_bit);
    
    for (int i = 0; i < NB_LINES; i++) {
        if (columns[0][NB_LINES - i - 1] == kept_bit) remaining_indexes.push_back(i);
    }
    
    for (int i = 1 ; i < NB_COLUMNS + 1; i++) {
        // Test de fin de parcours
        if (remaining_indexes.size() == 1) {
            break;
        }

        std::vector<bool> sub_column {};

        for (auto& index : remaining_indexes) {
            sub_column.push_back(columns[i][NB_LINES - index - 1]);
        }

        kept_bit = (std::count(sub_column.begin(), sub_column.end(), 1) >= (sub_column.size()/2.0) == rating_bit);
        std::vector<int> temp_indexes = remaining_indexes;
        remaining_indexes.clear();
        for (int j = 0; j < sub_column.size(); j++) {
            if (sub_column[j] == kept_bit) remaining_indexes.push_back(temp_indexes[j]);
        };
    }   

    return remaining_indexes.front();
}

template <>
void day03<NB_LINES>::part_two() {
    std::cout << "Part two answer : " << std::stoi(input_str[get_rating(1)], 0, 2) * std::stoi(input_str[get_rating(0)], 0, 2) << "\n";
}

int main(int argc, char** argv) {
    day03<NB_LINES> day03;
    day03.part_one();
    day03.part_two();
}