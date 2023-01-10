#include "day16.h"


day16::day16() {
    auto input_str = readFile("inputs/day16.input");
    for (const auto& c : input_str[0]) bin_str.append(hex_bin[c]);
    char c = ' ';
    trail_index = bin_str.size() - 1;
    while ((c = bin_str[trail_index]) != '1') --trail_index;
    parse_packets();
}

packet* parse_packet(const std::string* s, int* read_index) {
    std::string type_id = s->substr(*read_index + HEADER_SIZE, HEADER_SIZE);
    if (type_id == "100") {
        return new literal_value_packet(s, read_index);
    }
    else {
        return new operator_packet(s, read_index);
    }
}

void day16::parse_packets() {
    int read_index = 0;
    while (read_index <= trail_index) 
        packets.push_back(parse_packet(&bin_str, &read_index));
}

literal_value_packet::literal_value_packet(const std::string* s, int* read_index) {
    packet_version = s->substr(*read_index, HEADER_SIZE);
    type_id = s->substr(*read_index + 3, HEADER_SIZE);
    *read_index += 2 * HEADER_SIZE;
    bool found = false;
    while (!found) {
        if ((*s)[*read_index] == '0') found = true;
        binary_number.append(s->substr(*read_index + 1, BINARY_NUMBER_SIZE));
        *read_index += 5;
    }   
}

operator_packet::operator_packet(const std::string* s, int* read_index) {
    packet_version = s->substr(*read_index, HEADER_SIZE);
    type_id = s->substr(*read_index + 3, HEADER_SIZE);
    length_type_id = (*s)[*read_index + 6];
    *read_index += 7;
    if (length_type_id == '0') {
        length_sub_packets = stoi(s->substr(*read_index, 15), 0, 2);
        *read_index += 15;
        int starting_index = *read_index;
        while (*read_index != starting_index + length_sub_packets) {
            sub_packets.push_back(parse_packet(s, read_index));
        }
    }

    else {
        nb_sub_packets = stoi(s->substr(*read_index, 11), 0, 2);
        *read_index += 11;
        while (sub_packets.size() != nb_sub_packets) {
            sub_packets.push_back(parse_packet(s, read_index));       
        }
    }
}

void add_version(int* version_sum, const packet* packet) {
    if (packet->type_id == "100") *version_sum += std::stoi(packet->packet_version, 0, 2);
    else {
        *version_sum += std::stoi(packet->packet_version, 0, 2);
        for (auto& subp : static_cast<const operator_packet*>(packet)->sub_packets)
            add_version(version_sum, subp);
    }
}

int day16::total_versions() {
    int version_sum = 0;
    for (const auto& packet : packets) {
        add_version(&version_sum, packet);
    }
    return version_sum;
}

void apply_value(const packet* packet, op func, long* prev_operand) {
    if (packet->type_id == "100") 
        *prev_operand = func.operator()(*prev_operand, std::stol(static_cast<const literal_value_packet*>(packet)->binary_number, 0, 2));
    else {
        if (comparison_set.find(packet->type_id) != comparison_set.end()) {
            const operator_packet* p = static_cast<const operator_packet*>(packet);
            long operand1 = 0;
            long operand2 = 0;
            apply_value(p->sub_packets[0], op_map["000"], &operand1);
            apply_value(p->sub_packets[1], op_map["000"], &operand2);
            long final_op = op_map[p->type_id].operator()(operand1, operand2);
            *prev_operand = func.operator()(*prev_operand, final_op);
        }
        else {
            long sub_operation_sum = base_number_map[static_cast<const operator_packet*>(packet)->type_id];
            for (auto& subp : static_cast<const operator_packet*>(packet)->sub_packets)
                apply_value(subp, op_map[static_cast<const operator_packet*>(packet)->type_id], &sub_operation_sum);
            *prev_operand = func.operator()(*prev_operand, sub_operation_sum);
        }
    }
}

long day16::total_values() {
    long operand = base_number_map[static_cast<operator_packet*>(packets[0])->type_id];
    for (const auto& packet : packets) 
        apply_value(packet, op_map[static_cast<operator_packet*>(packets[0])->type_id], &operand);
    return operand;
}

void day16::part_one() {
    std::cout << "Part one answer : " << total_versions() << "\n";
}

void day16::part_two() {
    std::cout << "Part two answer : " << total_values() << "\n";
}

int main(int argc, const char** argv) {
    day16 day16;    
    day16.part_one();
    day16.part_two();
}