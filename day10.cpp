#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::vector<int>> board;

int count_endings(board &grid, int i, int j, int next) {
    if (grid[i][j] != next) {
        return 0;
    }
    if (grid[i][j] == 9) {
        grid[i][j] = -1;
        return 1;
    }
    int sum = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::pair<int, int>> directions {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for (std::pair<int, int> d : directions) {
        int i_x = i + d.first;
        int j_x = j + d.second;
        if (i_x < 0 || i_x >= rows || j_x < 0 || j_x >= cols) {
            continue;
        }
        sum += count_endings(grid, i_x, j_x, next + 1);
    }
    return sum;
}

int count_paths(const board &grid, int i, int j, int next) {
    if (grid[i][j] != next) {
        return 0;
    }
    if (grid[i][j] == 9) {
        return 1;
    }
    int sum = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::pair<int, int>> directions {{1,0}, {-1,0}, {0,1}, {0,-1}};
    for (std::pair<int, int> d : directions) {
        int i_x = i + d.first;
        int j_x = j + d.second;
        if (i_x < 0 || i_x >= rows || j_x < 0 || j_x >= cols) {
            continue;
        }
        sum += count_paths(grid, i_x, j_x, next + 1);
    }
    return sum;
}

int main() {
    std::ifstream file("day10.txt");
    board grid;
    std::string line;
    while (getline(file, line)) {
        grid.push_back({});
        for (char c : line) {
            grid.back().push_back(c - '0');
        }
    }
    int part_one = 0;
    int part_two = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board temp = grid;
            part_one += count_endings(temp, i, j, 0);
            part_two += count_paths(grid, i, j, 0);
        }
    }
    std::cout << part_one << std::endl;
    std::cout << part_two << std::endl;
    file.close();
    return 0;
}