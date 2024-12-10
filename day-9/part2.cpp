#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdint>

// Day 9 Part 2
int main()
{
    // int total = 0;
    std::ifstream input("input.txt");

    std::string line;
    std::vector<int64_t> numbers;
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

    int64_t start_idx = 0;
    std::vector<int64_t> indices;
    std::vector<int64_t> free_space_indicies;
    // Search from Behind:
    int64_t end_idx = numbers.size() - 1;
    for (int i = numbers.size() - 1; i >= 0; i--)
    {
        int64_t curr_int = numbers[i];
        int64_t next_int = numbers[i];

        indices.clear();
        while (curr_int != -1 && curr_int == next_int)
        {
            indices.push_back(i);
            i--;
            next_int = numbers[i];
        }

        std::cout << "Capacity of " << curr_int << " - " << indices.size() << std::endl;

        for (size_t j = 0; j < indices.size(); j++)
        {
            std::cout << indices[j] << " - " << numbers[indices[j]] << std::endl;
        }

        if (indices.size() != 0)
        {
            i++;
            int64_t target_capacity = indices.size();
            int64_t index_limit = indices[indices.size() - 1];
            // Find Free Space:
            std::cout << "Target Cap: " << target_capacity << std::endl;
            bool isFound = false;
            for (size_t j = 0; j < index_limit; j++)
            {
                if (isFound)
                {
                    break;
                }
                free_space_indicies.clear();
                int64_t curr_num = numbers[j];

                while (curr_num == -1)
                {
                    if (j == index_limit)
                    {
                        break;
                    }
                    free_space_indicies.push_back(j);
                    if (free_space_indicies.size() == target_capacity)
                    {
                        for (size_t k = 0; k < free_space_indicies.size(); k++)
                        {
                            std::cout << "Found: " << free_space_indicies[k] << std::endl;
                            uint64_t temp_idx = numbers[indices[k]];
                            numbers[indices[k]] = numbers[free_space_indicies[k]];
                            numbers[free_space_indicies[k]] = temp_idx;
                        }
                        isFound = true;
                        break;
                    }

                    j++;
                    curr_num = numbers[j];
                }
            }
        }
    }

    for (size_t i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << " ";
    }
    int64_t total = 0;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == -1)
        {
            continue;
        }
        // std::cout << numbers[i] << " ";

        total += numbers[i] * i;
    }

    std::cout << std::endl;
    // std::cout << line << std::endl;
    std::cout << total << std::endl;
}