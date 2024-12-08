#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

struct Cords
{
    int x;
    int y;
    char typeOfChar;
};

std::vector<int> split(const std::string &s, char delim)
{
    std::vector<int> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(std::stoi(item));
    }

    return result;
}

void PrintCord(const Cords cord)
{
    std::cout << "(" << cord.x << "," << cord.y << ") - " << cord.typeOfChar << " ";
};

std::vector<Cords> DrawCords(const Cords first,
                             const Cords second,
                             const std::vector<std::vector<Cords>> cords)
{
    std::vector<Cords> total_cords;
    size_t y_lim = cords.size() - 1;
    size_t x_lim = cords[0].size() - 1;
    std::cout << "First Cord:";
    Cords distance_offset = {
        first.x - second.x,
        first.y - second.y, ' '};

    Cords new_cord = {
        first.x + distance_offset.x,
        first.y + distance_offset.y, ' '};

    total_cords.push_back(first);
    if (new_cord.x >= 0 && new_cord.x <= x_lim && new_cord.y >= 0 && new_cord.y <= y_lim)
    {
        PrintCord(new_cord);
        total_cords.push_back(new_cord);
    }
    while (new_cord.x >= 0 && new_cord.x <= x_lim && new_cord.y >= 0 && new_cord.y <= y_lim)
    {

        total_cords.push_back(new_cord);
        new_cord = {
            new_cord.x + distance_offset.x,
            new_cord.y + distance_offset.y, ' '};
    }
    return total_cords;
}

int main()
{
    int total = 0;
    std::ifstream input("input.txt");

    std::string line;

    std::vector<std::vector<Cords>> cordinates;
    std::vector<Cords> searched_chars;
    std::vector<Cords> antinode_locations;
    int y_cord = 0;
    while (std::getline(input, line))
    {
        std::vector<Cords> tempCords;
        for (size_t x = 0; x < line.size(); x++)
        {
            Cords curr_cord =
                {
                    (int)x,
                    y_cord,
                    line[x]};
            tempCords.push_back(curr_cord);
        }
        cordinates.push_back(tempCords);
        y_cord++;
    }

    for (size_t y = 0; y < cordinates.size(); y++)
    {
        for (size_t x = 0; x < cordinates[y].size(); x++)
        {
            Cords cord = cordinates[y][x];

            if (cord.typeOfChar != '.')
            {

                searched_chars.push_back(cord);
                // PrintCord(cord);
                std::cout << std::endl;
            }
        }
    }

    for (size_t i = 0; i < searched_chars.size(); i++)
    {
        Cords cord = searched_chars[i];
        // PrintCord(cord);
        std::cout << std::endl;
        for (size_t j = 0; j < searched_chars.size(); j++)
        {
            Cords other_cord = searched_chars[j];
            if (j == i)
            {
                continue;
            }

            if (other_cord.typeOfChar != cord.typeOfChar)
            {
                continue;
            }

            // PrintCord(other_cord);
            auto result = DrawCords(cord, other_cord, cordinates);
            for (size_t k = 0; k < result.size(); k++)
            {
                antinode_locations.push_back(result[k]);
            }
        }
        std::cout << std::endl;
    }

    for (size_t i = 0; i < antinode_locations.size(); i++)
    {
        Cords antinode_location = antinode_locations[i];

        cordinates[antinode_location.y][antinode_location.x].typeOfChar = '#';
    }

    for (size_t y = 0; y < cordinates.size(); y++)
    {
        for (size_t x = 0; x < cordinates[y].size(); x++)
        {
            Cords cord = cordinates[y][x];

            if (cord.typeOfChar == '#')
            {
                total++;
            }
        }
    }

    std::cout << total << std::endl;
}