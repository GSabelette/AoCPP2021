#pragma once

#include <iostream>
#include <fstream>
#include <chrono>

#include <algorithm>
#include <functional>
#include <utility>
#include <numeric>
#include <cmath>
#include <tgmath.h>

#include <cstdint>
#include <string>
#include <cstring>
#include <vector>
#include <bitset>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <iterator>

inline std::vector<std::string> readFile(const char* filename) {
    const auto start = std::chrono::high_resolution_clock::now();
    std::ifstream inputFile {};
    inputFile.open(filename);
    if (!inputFile.is_open()) throw std::runtime_error("File not found");

    std::vector<std::string> out;
    std::string bufferedString;

    while(std::getline(inputFile, bufferedString)) {
        out.push_back(bufferedString);
    }
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Opening file " << filename << " took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns \n";
    return out;
}

inline uint64_t fast_atol(const char* buf, size_t len = 0, int base = 10) {
    if (len == 0) {
        len = std::strlen(buf);
    }
    unsigned int n = 0;
    while (len--) {
        if (!std::isdigit(*buf)) {
            return n;
        }
        n = (n * base) + (*buf++ - '0');
    }
    return n;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> v) {
    os << "Vector {";
    for (const auto& t : v) os << t << ", ";
    os << "}";
    return os;
}

template <typename T, size_t n>
std::ostream& operator<<(std::ostream& os, const std::array<T, n> a) {
    os << "Array {";
    for (const auto& t : a) os << t << ", ";
    os << "}";
    return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T,S> p) {
    os << "Pair<" << p.first << ", " << p.second << ">";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> s) {
    os << "Set [";
    for (const auto& t : s) os << t << ", ";
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T> s) {
    os << "Set [";
    for (const auto& t : s) os << t << ", ";
    os << "]";
    return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::map<T,S> m) {
    os << "Map (";
    for (const auto& kp : m) os << "<" << kp.first << ", " << kp.second << ">, ";
    os << ")";  
    return os;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<T,S> m) {
    os << "Map (";
    for (const auto& kp : m) os << "<" << kp.first << ", " << kp.second << ">, ";
    os << ")";  
    return os;
}

template <typename T, typename S, typename U>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<T,S,U> m) {
    os << "Map (";
    for (const auto& kp : m) os << "<" << kp.first << ", " << kp.second << ">, ";
    os << ")";  
    return os;
}

std::vector<std::string> split_string(std::string s, std::string delim) {
    std::vector<std::string> parsed_vector {};
    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos)
    {
        parsed_vector.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    parsed_vector.push_back(s.substr(start));
    return parsed_vector;
}

template <typename T>
std::vector<T> split_string(std::string s, std::string delim, std::function<T(std::string)> func) {
    std::vector<T> parsed_vector {};
    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos)
    {
        parsed_vector.push_back(func(s.substr(start, end - start)));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    parsed_vector.push_back(func(s.substr(start)));
    return parsed_vector;
}

template <typename T, typename U>
struct PairHash {
    size_t operator()(const std::pair<T,U>& p) const {
        return std::hash<T>()(p.first) ^ std::hash<U>()(p.second); 
    }
};

template <typename T, typename U>
struct UserPairHash {
    size_t operator()(const std::pair<T, U> p) const {
        return (p.first)() ^ (p.first)();
    }
};

bool is_upper_case(std::string s) {
    for (auto& c : s) if (isupper(c) != c) return false;
    return true;
}

