#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdint>
int main()
{
    // int total = 0;
    std::ifstream input("input.txt");

    std::string line;
    std::vector<int> numbers;
    std::getline(input, line);

    int64_t id = 0;
    for (size_t i = 0; i < line.size(); i++)
    {
        char curr_char = line[i];
        if (i % 2 == 0)
        {
            // Blocks:
            for (int j = 0; j < (curr_char - '0'); j++)
            {
                numbers.push_back(id);
            }

            id++;
        }
        else
        {
            // Free Space:
            for (int j = 0; j < (curr_char - '0'); j++)
            {
                numbers.push_back(-1);
            }
        }
    }

    for (size_t i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << " ";
    }

    std::cout << std::endl;

    int64_t end_idx = numbers.size() - 1;

    for (size_t i = 0; i < numbers.size(); i++)
    {
        int64_t curr_number = numbers[i];

        if (i == end_idx)
        {
            break;
        }
        if (curr_number == -1)
        {
            int64_t ending_number = numbers[end_idx];
            while (ending_number == -1)
            {
                end_idx--;
                ending_number = numbers[end_idx];
            }

            numbers[i] = ending_number;
            numbers[end_idx] = curr_number;
            end_idx--;
        }
    }
    int64_t total = 0;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == -1)
        {
            break;
        }
        std::cout << numbers[i] << " ";

        total += numbers[i] * i;
    }

    std::cout << std::endl;
    std::cout << line << std::endl;
    std::cout << total << std::endl;
}