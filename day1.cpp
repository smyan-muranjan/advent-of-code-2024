#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

int main() {
    std::ifstream file("day1.txt");
    std::vector<int> left;
    std::vector<int> right;
    std::string line;
    while (getline(file, line)) {
        int left_num, right_num;
        std::istringstream iss(line);
        iss >> left_num >> right_num;
        left.push_back(left_num);
        right.push_back(right_num);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    int part_one = 0;
    for (int i = 0; i < left.size(); i++) {
        part_one += std::abs(left[i] - right[i]);
    }
    file.close();
    std::cout << part_one << std::endl;

    std::unordered_map<int, int> count;
    for (int num : right) {
        count[num]++;
    }
    int part_two = 0;
    for (int num : left) {
        part_two += num * count[num];
    }
    std::cout << part_two << std::endl;
    return 0;
}