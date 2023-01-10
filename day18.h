#pragma once

#include "common.h"

struct Node {
    std::pair<Node*, Node*> lr;
    int val;

    bool isPair();
    int magnitude();

    Node(std::string s);
    Node(Node& left, Node& right);

    Node operator+(const Node& other) {
        return *this+other;
    }
};

std::ostream& operator<<(std::ostream& os, Node& n) {
    if (n.isPair()) os << "[" << *n.lr.first << ", " << *n.lr.second << "]";
    else os << n.val;
    return os;
}

struct day18 {
    std::vector<std::string> input;
    std::vector<Node> nodes;

    day18();

    void part_one();
    void part_two();
};

