#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
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

    for (size_t i = 0; i < first_num_list.size(); i++)
    {
        int found_times = 0;
        std::vector<int>::iterator begin = std::find(second_num_list.begin(), second_num_list.end(),
                                                     first_num_list[i]);

        while (begin != second_num_list.end())
        {
            begin = std::find(begin + 1, second_num_list.end(),
                              first_num_list[i]);
            found_times++;
        }
        total += first_num_list[i] * found_times;
    }

    std::cout << total << std::endl;
    input.close();
    return 0;
}
