#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

int main()
{
    std::ifstream input("example1.txt");

    std::string line;
    std::getline(input, line);

    // std::cout << line << std::endl;

    uint64_t id = 0;
    uint64_t empty = 0;
    std::vector<char> map;
    std::string map_chars;
    for (size_t i = 0; i < line.size(); i++)
    {
        char curr_char = line[i];
        if (i % 2 == 0)
        {
            // Memory:
            for (size_t j = 0; j < (curr_char - '0'); j++)
            {
                /* code */
                map_chars.append(std::to_string(id));
            }

            id++;
        }
        else
        {
            // Free Space;
            for (size_t j = 0; j < (curr_char - '0'); j++)
            {
                /* code */
                map_chars.append(".");
                empty++;
            }
        }
    }

    std::cout << map_chars << std::endl;
    uint64_t end_idx = map_chars.size() - 1;
    for (size_t i = 0; i < map_chars.size(); i++)
    {
        char curr_char = map_chars[i];

        if (curr_char == '.')
        {
            char end_char = map_chars[end_idx];
            while (end_char == '.')
            {
                end_idx--;
                end_char = map_chars[end_idx];
            }

            map_chars[i] = map_chars[end_idx];
            map_chars[end_idx] = curr_char;
            end_idx--;
        }

        if (end_idx == i)
        {
            break;
        }
    }

    uint64_t total = 0;
    std::cout << map_chars.size() << std::endl;
    for (size_t i = 0; i < map_chars.size(); i++)
    {
        if (map_chars[i] == '.')
        {
            break;
        }
        total += i * (map_chars[i] - '0');
    }

    // std::cout << map_chars << std::endl;
    std::cout << total << std::endl;
}