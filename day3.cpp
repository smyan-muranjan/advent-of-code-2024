#include <iostream>
#include <regex>
#include <fstream>

void part_one(const std::string &content) {
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    auto words_begin = std::sregex_iterator(content.begin(), content.end(), pattern);
    auto words_end = std::sregex_iterator();
    int res = 0;
    while (words_begin != words_end) {
        std::smatch match = *words_begin;
        res += std::stoi(match[1]) * std::stoi(match[2]);
        words_begin++;
    }
    std::cout << res << std::endl;
}

void part_two(const std::string &content) {
    std::regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    auto words_begin = std::sregex_iterator(content.begin(), content.end(), pattern);
    auto words_end = std::sregex_iterator();
    int res = 0;
    bool do_multiply = true;
    while (words_begin != words_end) {
        std::smatch match = *words_begin;
        if (match[0] == "do()") {
            do_multiply = true;
        } else if (match[0] == "don't()") {
            do_multiply = false;
        } else if (do_multiply) {
            res += std::stoi(match[1]) * std::stoi(match[2]);
        }
        words_begin++;
    }
    std::cout << res << std::endl;
}

int main() {
    std::ifstream file("day3.txt");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    part_one(content);
    part_two(content);
    file.close();
    return 0;
}