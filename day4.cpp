#include <iostream>
#include <fstream>
#include <vector>

void part_one(const std::vector<std::string> &grid, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 'X') {
                continue;
            }
            // right
            if (j + 3 < cols && std::string({grid[i][j+1], grid[i][j+2], grid[i][j+3]}) == "MAS") {
                count++;
            }
            // left
            if (j - 3 >= 0 && std::string({grid[i][j-1], grid[i][j-2], grid[i][j-3]}) == "MAS") {
                count++;
            }
            // up
            if (i - 3 >= 0 && std::string({grid[i-1][j], grid[i-2][j], grid[i-3][j]}) == "MAS") {
                count++;
            }
            // down
            if (i + 3 < rows && std::string({grid[i+1][j], grid[i+2][j], grid[i+3][j]}) == "MAS") {
                count++;
            }
            // up-left
            if (j - 3 >= 0 && i - 3 >= 0 && std::string({grid[i-1][j-1], grid[i-2][j-2], grid[i-3][j-3]}) == "MAS") {
                count++;
            }
            // up-right
            if (j + 3 < cols && i - 3 >= 0 && std::string({grid[i-1][j+1], grid[i-2][j+2], grid[i-3][j+3]}) == "MAS") {
                count++;
            }
            // down-left
            if (j - 3 >= 0 && i + 3 < rows && std::string({grid[i+1][j-1], grid[i+2][j-2], grid[i+3][j-3]}) == "MAS") {
                count++;
            }
            // down-right
            if (j + 3 < cols && i + 3 < rows && std::string({grid[i+1][j+1], grid[i+2][j+2], grid[i+3][j+3]}) == "MAS") {
                count++;
            }
        }
    }
    std::cout << count << std::endl;
}

void part_two(const std::vector<std::string> &grid, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 'A') {
                continue;
            }
            if (i >= 1 && i < rows - 1 && j >= 1 && j < cols - 1) {
                std::string left({grid[i - 1][j - 1], grid[i + 1][j + 1]});
                std::string right({grid[i - 1][j + 1], grid[i + 1][j - 1]});
                if ((left == "MS" || left == "SM") && (right == "MS" || right == "SM")) { 
                    count++;
                }
            }
        }
    }
    std::cout << count << std::endl;
}

int main() {
    std::ifstream file("day4.txt");
    std::vector<std::string> grid;
    std::string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    part_one(grid, rows, cols);
    part_two(grid, rows, cols);
    file.close();
}