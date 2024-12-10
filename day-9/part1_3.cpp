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

    std::cout << line << std::endl;

    int id = 0;
    int empty = 0;
    std::vector<char> map;
    for (size_t i = 0; i < line.size(); i++)
    {

        if (i % 2 == 0)
        {
            // Block file:
            for (int j = 0; j < (line[i] - '0'); j++)
            {
                map.push_back((char)(id + '0'));
            }

            id++;
        }
        else
        {
            for (int j = 0; j < (line[i] - '0'); j++)
            {
                map.push_back('.');
                empty++;
            }
        }
    }
    std::cout << empty << std::endl;
    int end_idx = map.size() - 1;
    int times_forwarded = 0;
    for (size_t i = 0; i < map.size(); i++)
    {
        char curr_char = map[i];
        if (curr_char == '.')
        {
            map[i] = map[end_idx];
            map[end_idx] = curr_char;
            end_idx--;
            times_forwarded++;
        }

        if (times_forwarded == empty)
        {
            break;
        }
    }
    int total = 0;
    for (int i = 0; i < (int)map.size(); i++)
    {
        char curr = map[i];
        int num = curr - '0';
        std::cout << curr;
        if (curr == '.')
        {
            break;
        }
        total += num * i;
    }

    std::cout << total << std::endl;
}