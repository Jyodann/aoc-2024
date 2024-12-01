#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
    std::ifstream input("input.txt");

    std::string line;
    std::string delim = "   ";
    int first_num, second_num, total = 0;

    std::vector<int> first_num_list, second_num_list;

    while (std::getline(input, line))
    {
        size_t idx = line.find(delim);
        first_num = std::stoi(line.substr(0, idx));
        second_num = std::stoi(line.substr(idx + 3, line.size()));

        first_num_list.push_back(first_num);
        second_num_list.push_back(second_num);
    }
    std::sort(first_num_list.begin(), first_num_list.end());
    std::sort(second_num_list.begin(), second_num_list.end());

    for (size_t i = 0; i < first_num_list.size(); i++)
    {
        total += abs(first_num_list[i] - second_num_list[i]);
    }

    std::cout << total << std::endl;
    input.close();
    return 0;
}
