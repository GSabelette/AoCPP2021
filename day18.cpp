#include "day18.h"

day18::day18() {
    input = readFile("inputs/day18.input");
    for (const auto& s : input) {
        nodes.emplace_back(Node(s));
    }
}

int central_comma_index(std::string s) {
    // If s doesn't start with a parenthesis we can just find the first comma
    if (s[0] != '[') return std::find(s.begin(), s.end(), ',')-s.begin()+1;

    int counter = 1;
    int index = 1;
    while (counter > 0) {
        switch (s[index]) {
            case '[' : 
                counter++;
                break;
            case ']' :
                counter--;
                break;
            default :
                ;
        }
        ++index;
    }
    return index+1;
}

int getLeftNumber(std::string& s, size_t index) {
    if (index >= s.length() || index < 0) return -1;
    for (std::string::iterator it = (s.begin() + index - 1); it != s.begin(); it--) {
        if (std::isdigit(*it)) return it - s.begin();
    }
    return -1;
}

int getRightNumber(std::string& s, size_t index) {
    if (index >= s.length() || index < 0) return -1;
    for (std::string::iterator it = (s.begin() + index + 1); it != s.end(); it++) {
        if (std::isdigit(*it)) return it - s.begin();
    }
    return -1;
}

void addToLeft(std::string& s, int num, int pos) {
    int leftIndex = getLeftNumber(s, pos);
    if (leftIndex == -1) return;
    int leftmost = leftIndex;
    while (leftmost > 0 && std::isdigit(s[leftmost - 1])) leftmost--;
    auto sum = std::stol(s.substr(leftmost, leftIndex - leftmost + 1));
    sum += num;
    s.replace(leftmost, leftIndex - leftmost + 1, std::to_string(sum));
}

void addToRight(std::string& s, int num, int pos) {
    int rightIndex = getRightNumber(s, pos);
    if (rightIndex == -1) return;
    size_t rightmost = rightIndex;
    while (rightmost < s.length() && std::isdigit(s[rightmost + 1])) rightmost++;
    auto sum = std::stol(s.substr(rightIndex, rightmost - rightIndex + 1));
    sum += num;
    s.replace(rightIndex, rightmost - rightIndex + 1, std::to_string(sum));
}

void explode(std::string& s, int pos) {
    size_t leftRightPos = pos;
    while (leftRightPos < s.length() && std::isdigit(s[leftRightPos + 1])) leftRightPos++;
    int explodeLeft = std::stoi(s.substr(pos, leftRightPos - pos + 1));

    int rightLeftPos = leftRightPos + 2;
    size_t rightRightPos = rightLeftPos;
    while (rightRightPos < s.length() && std::isdigit(s[rightRightPos + 1])) rightRightPos++;
    int explodeRight = std::stoi(s.substr(rightLeftPos, rightRightPos - rightLeftPos + 1));

    s.replace(pos-1, 5 + (leftRightPos - pos) + (rightRightPos - rightLeftPos), "0");
    // pos-1 is where the new 0 is located | we have to add to the right first else the 0 could be shifted
    addToRight(s, explodeRight, pos-1);
    addToLeft(s, explodeLeft, pos-1);
}

void split(std::string& s, int pos) {
    float num = std::stoi(s.substr(pos, 2));
    int leftNum = std::floor(num/2);
    int rightNum = std::ceil(num/2);
    s.replace(pos, 2, std::string("[" + std::to_string(leftNum) + "," + std::to_string(rightNum)) + "]");
}

bool checkExplode(std::string& s) {
    int depth = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        depth += (*it == '[');
        depth -= (*it == ']');
        if (depth >= 5) {
            explode(s, it - s.begin() + 1);
            return true;
        } 
    }
    return false;
}

bool checkSplit(std::string& s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (std::isdigit(*it)) {
            if (std::isdigit(*(++it))) {
                split(s, it - s.begin() - 1);
                return true;
            }
        } 
    }
    return false;
}

void reduce(std::string& s) {
    bool operationPerformed = true;
    while (operationPerformed) {
        if (checkExplode(s)) continue;
        if (checkSplit(s)) continue;
        operationPerformed = false;
    }
}

std::string add(std::string& s1, std::string& s2) {
    return std::string('[' + s1 + ',' + s2 + ']');
}

Node::Node(std::string s) {
    if (s[0] == '[') {
        int central_comma = central_comma_index(std::string(s, 1));
        lr.first = new Node(std::string(s, 1, central_comma));
        lr.second = new Node(std::string(s, central_comma+1, s.length()));
    } else {
        val = static_cast<int>(s[0] - '0');
    }
}

Node::Node(Node& left, Node& right) {
    lr.first = &left; 
    lr.second = &right;
}

bool Node::isPair() {
    return (lr.first || lr.second);
}

int Node::magnitude() {
    if (isPair()) return lr.first->magnitude() * 3 + lr.second->magnitude() * 2;
    return val;
}

void day18::part_one() {
    std::string sumString = input.front();
    for (auto s = input.begin() + 1; s != input.end(); ++s) {
        sumString = add(sumString, *s);
        reduce(sumString);
    }
    Node n(sumString);
    printf("Final magnitude : %d\n", n.magnitude());
}

void day18::part_two() {
    size_t maxMagnitude = 0;
    for (auto sumString : input) {
        for (auto s : input) {
            if (sumString != s) {
                std::string totString = add(sumString, s);
                reduce(totString);
                size_t mag = Node(totString).magnitude();
                if (mag > maxMagnitude) maxMagnitude = mag;
            }
        }
    }
    printf("Max magnitude : %ld\n", maxMagnitude);
}

int main() {
    day18 day18;
    day18.part_one();
    day18.part_two();
}