#include "day19.h"

std::array<std::function<Vector3(Vector3)>, 24> transformations {
    [](const Vector3& v) {return Vector3(v.x, v.y, v.z);},
    [](const Vector3& v) {return Vector3(v.x, v.z, -v.y);},
    [](const Vector3& v) {return Vector3(v.x, -v.y, -v.z);},
    [](const Vector3& v) {return Vector3(v.x, -v.z, v.y);},
    [](const Vector3& v) {return Vector3(v.y, v.x, -v.z);},
    [](const Vector3& v) {return Vector3(v.y, v.z, v.x);},
    [](const Vector3& v) {return Vector3(v.y, -v.x, v.z);},
    [](const Vector3& v) {return Vector3(v.y, -v.z, -v.x);},
    [](const Vector3& v) {return Vector3(v.z, v.x, v.y);},
    [](const Vector3& v) {return Vector3(v.z, v.y, -v.x);},
    [](const Vector3& v) {return Vector3(v.z, -v.x, -v.y);},
    [](const Vector3& v) {return Vector3(v.z, -v.y, v.x);},
    [](const Vector3& v) {return Vector3(-v.x, v.y, -v.z);},
    [](const Vector3& v) {return Vector3(-v.x, v.z, v.y);},
    [](const Vector3& v) {return Vector3(-v.x, -v.y,v.z);},
    [](const Vector3& v) {return Vector3(-v.x, -v.z, -v.y);},
    [](const Vector3& v) {return Vector3(-v.y, v.x, v.z);},
    [](const Vector3& v) {return Vector3(-v.y, v.z, -v.x);},
    [](const Vector3& v) {return Vector3(-v.y, -v.x, -v.z);},
    [](const Vector3& v) {return Vector3(-v.y, -v.z, v.x);},
    [](const Vector3& v) {return Vector3(-v.z, v.x, -v.y);},
    [](const Vector3& v) {return Vector3(-v.z, v.y, v.x);},
    [](const Vector3& v) {return Vector3(-v.z, -v.x, v.y);},
    [](const Vector3& v) {return Vector3(-v.z, -v.y, -v.x);},
};

std::array<Vector3,24> Vector3::possible_configs() const {
    std::array<Vector3, 24> configs;
    for (size_t i = 0; i < configs.size(); ++i) configs[i] = transformations[i](*this);
    return configs;
}

int16_t Vector3::distanceTo(Vector3 other) const {
    return std::abs(x - other.x) + std::abs(y - other.y) + std::abs(z - other.z);
}

day19::day19() {
    auto input = readFile("inputs/day19.input");
    input.erase(input.begin());
    Scanner scanner;
    for (auto& s : input) {
        if (s[1] == '-') {
            scanners.push_back(scanner);
            scanner.beacons.clear();
        }
        else scanner.beacons.emplace_back(Vector3(s));
    }
    scanners[0].position = Vector3(0,0,0);
    scanners[0].f = [](const Vector3& v){return v;};
    for (auto& s : scanners) s.computeDistances();
} 

void Scanner::computeDistances() {
    for (auto&& it = beacons.begin(); it != beacons.end(); ++it) {
        for (auto&& other = std::next(it, 1); other != beacons.end(); ++other) {
            distances_map[(*it).distanceTo(*other)] = std::pair<Vector3, Vector3>(*it, *other);
        }
    }
}

Vector3 Scanner::getOtherPosition(Scanner& other) {
    std::pair<Vector3, Vector3> pair; 
    std::pair<Vector3, Vector3> otherPair; 

    std::unordered_set<Vector3, Vector3> uniquePoints;

    bool found_one = false;
    // Loop through points to detect if we have 12 matching points.
    for (const auto& distVal : other.distances_map) {
        if (distances_map.contains(distVal.first)) {
            // If distances match we verify if both pairs of points are the same.
            Vector3 v1 = distances_map[distVal.first].second - distances_map[distVal.first].first;
            Vector3 v2 = distVal.second.second - distVal.second.first;
            for (auto& t : transformations) {
                Vector3 transformed_v2 = t(v2);
                if (transformed_v2 == v1 || -transformed_v2 == v1) {
                    // Just keeping a pair of matching points for later.
                    if (!found_one) {
                        pair = distances_map[distVal.first];
                        otherPair = distVal.second;
                        found_one = true;
                    }
                    uniquePoints.insert(distVal.second.first); 
                    uniquePoints.insert(distVal.second.second);
                }
            }
        }   
    }

    // If we have a match, we find corresponding transform.
    if (uniquePoints.size() >= 12) {
        Vector3 distVect = pair.second - pair.first;
        Vector3 otherDistVect = otherPair.second - otherPair.first;

        for (auto& t : transformations) {
            Vector3 transformed = t(otherDistVect);
            // When we find the correct transform we update and return the relative position of the scanner.
            if (transformed == distVect) {
                other.f = [&](const Vector3& v){return f(t(v));};
                return f((pair.first) - t(otherPair.first));
            }
            else if ((-transformed) == distVect) {
                other.f = [&](const Vector3& v){return f(t(v));};
                return f((pair.first) - t(otherPair.second));
            }
        }
    }
    return Vector3(0,0,0);
}

void day19::part_one() {
    std::vector<int8_t> unknownScanners;
    std::set<int8_t> foundScanners {0};
    for (int8_t i = 1; i < scanners.size(); ++i) unknownScanners.insert(unknownScanners.end(), i);  
    
    for (const auto& b : scanners[0].beacons) totalBeacons.insert(b);

    // We try matching one unknown scanner with every known scanner each loop.
    while (!unknownScanners.empty()) {
        // Just in case we don't find a match so we push back the scanner at the end of the queue.
        int8_t unknownScanIndex = *unknownScanners.begin();
        Scanner& otherScanner = scanners[unknownScanIndex];
        unknownScanners.erase(unknownScanners.begin());

        for (auto& found : foundScanners) {
            Vector3 otherPos = scanners[found].getOtherPosition(otherScanner);
            // In case of a match we update the unknown scanner and add its beacons to the total set.
            if (otherPos != Vector3(0,0,0)) {
                foundScanners.insert(unknownScanIndex);
                otherScanner.position = otherPos + scanners[found].position;
                for (const auto& b : otherScanner.beacons) totalBeacons.insert(otherScanner.f(b) + otherScanner.position);
                break;
            }
        }
        if (!foundScanners.contains(unknownScanIndex)) unknownScanners.push_back(unknownScanIndex);
    }

    std::cout << "Total Beacons : " << totalBeacons.size() << "\n";
}

void day19::part_two() {
    int16_t maxDistance = 0;
    for (const auto& s1 : scanners) {
        for (const auto& s2 : scanners) {
            if (s1.position.distanceTo(s2.position) > maxDistance) maxDistance = s1.position.distanceTo(s2.position);
        }
    }
    std::cout << "Largest Manhattan distance : " << maxDistance << "\n";
}

int main() {
    day19 day19;
    day19.part_one();
    day19.part_two();
}