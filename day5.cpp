#include <fstream>
#include <iostream>
#include <unordered_map>
#include <set>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>

bool check_ordering(const std::vector<int>& ordering, const std::unordered_map<int, std::set<int>>& prerequisites) {
    std::set<int> seen;
    std::set<int> all(ordering.begin(), ordering.end());

    for (int page : ordering) {
        if (prerequisites.count(page) == 0) {
            seen.insert(page);
            continue;
        }
        std::vector<int> required_prerequisites;
        std::set<int> possible_prerequisites = prerequisites.at(page);
        std::set_intersection(
            possible_prerequisites.begin(), possible_prerequisites.end(),
            all.begin(), all.end(),
            std::back_inserter(required_prerequisites)
        );
        std::vector<int> missing_prerequisites;
        std::set_difference(
            required_prerequisites.begin(), required_prerequisites.end(),
            seen.begin(), seen.end(),
            std::back_inserter(missing_prerequisites)
        );
        if (missing_prerequisites.size() > 0) {
            return false;
        }
        seen.insert(page);
    }

    return true;
}


std::vector<int> fix_ordering(const std::vector<int>& ordering, const std::unordered_map<int, std::set<int>>& prerequisites) {
    std::unordered_map<int, int> in_degree;
    std::unordered_map<int, std::set<int>> adj_list;
    for (int page : ordering) {
        if (!in_degree.count(page)) in_degree[page] = 0;
        if (prerequisites.count(page) != 0) {
            for (int prereq : prerequisites.at(page)) {
                if (std::find(ordering.begin(), ordering.end(), prereq) != ordering.end()) {
                    adj_list[prereq].insert(page);
                    in_degree[page]++;
                }
            }
        }
    }
    std::queue<int> q;
    for (int page : ordering) {
        if (in_degree[page] == 0) {
            q.push(page);
        }
    }

    std::vector<int> sorted_order;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        sorted_order.push_back(current);
        for (int neighbor : adj_list[current]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return sorted_order;
}

int main() {
    std::ifstream file("day5.txt");
    std::string line;
    std::unordered_map<int, std::set<int>> prerequisites;
    while (getline(file, line) && !line.empty()) {
        std::stringstream ss(line);
        int x, y;
        char delim;
        ss >> x >> delim >> y; // Read "X|Y"
        prerequisites[y].insert(x);
    }

    std::vector<std::vector<int>> orderings;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> ordering;
        std::string temp;
        while (getline(ss, temp, ',')) {
            ordering.push_back(std::stoi(temp));
        }
        orderings.push_back(ordering);
    }

    int part_one = 0;
    int part_two = 0;

    for (const auto& update : orderings) {
        if (check_ordering(update, prerequisites)) {
            part_one += update[update.size() / 2];
        } else {
            std::vector<int> corrected = fix_ordering(update, prerequisites);
            part_two += corrected[corrected.size() / 2];
        }
    }

    std::cout << part_one << std::endl;
    std::cout << part_two << std::endl;
    file.close();
    return 0;
}
