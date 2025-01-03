#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

bool part_one(const std::vector<int> &terms, long target, long current, int i) {
    if (current > target) {
        return false;
    }
    if (i == terms.size()) {
        if (current == target) {
            return true;
        } else {
            return false;
        }
    }
    return part_one(terms, target, current * terms[i], i + 1) || part_one(terms, target, current + terms[i], i + 1);
}

bool part_two(const std::vector<int> &terms, long target, long current, int i) {
    if (current > target) {
        return false;
    }
    if (i == terms.size()) {
        if (current == target) {
            return true;
        } else {
            return false;
        }
    }
    bool multiplication = part_two(terms, target, current * terms[i], i + 1);
    bool adding = part_two(terms, target, current + terms[i], i + 1);
    long concatenated_current = std::stol(std::to_string(current) + std::to_string(terms[i]));
    bool concatenating = part_two(terms, target, concatenated_current, i + 1);
    return multiplication || adding || concatenating;
}

int main() {
    std::ifstream file("day7.txt");
    std::string line;
    std::vector<long> targets;
    std::vector<std::vector<int>> terms;
    while (getline(file, line)) {
        int colon_position = line.find(':');
        targets.push_back(std::stol(line.substr(0, colon_position)));
        std::stringstream ss(line.substr(colon_position + 1));
        int num;
        std::vector<int> current_terms;
        while (ss >> num) {
            current_terms.push_back(num);
        }
        terms.push_back(current_terms);
    }
    long res_one = 0;
    long res_two = 0;
    for (int i = 0; i < targets.size(); i++) {
        if (part_one(terms[i], targets[i], 0, 0)) {
            res_one += targets[i];
        }
        if (part_two(terms[i], targets[i], 0, 0)) {
            res_two += targets[i];
        }
    }
    std::cout << res_one << std::endl;
    std::cout << res_two << std::endl;
    file.close();
    return 0;
}