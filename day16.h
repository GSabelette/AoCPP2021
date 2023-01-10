#pragma once

#include "common.h"

#define HEADER_SIZE 3
#define INPUT_SIZE 1366 * 4
#define BINARY_NUMBER_SIZE 4    

typedef std::function<long(long,long)> op;


std::unordered_map<char, std::string> hex_bin = {{'0', "0000"},
                                                 {'1', "0001"},
                                                 {'2', "0010"},
                                                 {'3', "0011"},
                                                 {'4', "0100"},
                                                 {'5', "0101"},
                                                 {'6', "0110"},
                                                 {'7', "0111"},
                                                 {'8', "1000"},
                                                 {'9', "1001"},
                                                 {'A', "1010"},
                                                 {'B', "1011"},
                                                 {'C', "1100"},
                                                 {'D', "1101"},
                                                 {'E', "1110"},
                                                 {'F', "1111"}};

std::map<std::string, op> op_map = {{"000", [](long a, long b)->long{return a+b;}},
                                    {"001", [](long a, long b)->long{return a*b;}},             
                                    {"010", [](long a, long b)->long{return std::min(a,b);}},
                                    {"011", [](long a, long b)->long{return std::max(a,b);}},
                                    {"101", [](long a, long b)->long{return a>b;}},
                                    {"110", [](long a, long b)->long{return a<b;}},
                                    {"111", [](long a, long b)->long{return a==b;}}
};

std::unordered_set<std::string> comparison_set = {"101", "110", "111"};

std::unordered_map<std::string, long> base_number_map = {{"000", 0},
                                                         {"001", 1},
                                                         {"010", std::numeric_limits<long>::max()},
                                                         {"011", std::numeric_limits<long>::min()}
};
struct packet {
    public:
        std::string packet_version;
        std::string type_id;
};

struct literal_value_packet : packet {
    public:
        std::string binary_number;
        literal_value_packet(const std::string* s, int* read_index);
};

struct operator_packet : packet {
    public: 
        char length_type_id;
        int nb_sub_packets;
        int length_sub_packets;    
        std::vector<packet*> sub_packets;
        operator_packet(const std::string* s, int* read_index); 
};

struct day16 {
    std::string bin_str;
    std::bitset<INPUT_SIZE> binary_message;
    std::vector<packet*> packets;
    int trail_index;

    void parse_packets();
    int total_versions();
    long total_values();

    day16();

    void part_one();
    void part_two();
};