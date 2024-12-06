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
    bool visited;
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
    std::cout << "(" << cord.x << "," << cord.y << ") - " << cord.typeOfChar << " " << "Visited: " << cord.visited << " ";
};

const Cords directions[] = {
    {0, -1, false, 'u'},
    {1, 0, false, 'r'},
    {0, 1, false, 'd'},
    {-1, 0, false, 'l'},
};

int main()
{
    int total = 0;
    std::ifstream input("example.txt");

    std::string line;

    std::vector<std::vector<Cords>> cordinates;
    std::vector<Cords> repeatVisit;
    int y_cord = 0;
    Cords current_location, starting_pos;
    while (std::getline(input, line))
    {
        std::vector<Cords> tempCords;
        for (size_t x = 0; x < line.size(); x++)
        {
            Cords curr_cord =
                {
                    x,
                    y_cord,
                    false,
                    line[x]};
            tempCords.push_back(curr_cord);

            if (line[x] == '^')
            {
                starting_pos = current_location = curr_cord;
            }
        }
        cordinates.push_back(tempCords);
        y_cord++;
    }

    int current_facing_dir_idx = 0;

    Cords nextLocation = current_location;
    Cords direction;
    while (true)
    {

        direction = directions[current_facing_dir_idx];
        int next_y = current_location.y + direction.y;
        int next_x = current_location.x + direction.x;

        if (next_y < 0 || next_y > cordinates.size() - 1)
        {
            cordinates[current_location.y][current_location.x].visited = true;
            break;
        }

        if (next_x < 0 || next_x > cordinates[0].size() - 1)
        {
            cordinates[current_location.y][current_location.x].visited = true;
            break;
        }
        nextLocation = cordinates[next_y][next_x];
        PrintCord(nextLocation);

        if (nextLocation.typeOfChar != '#')
        {
            cordinates[current_location.y][current_location.x].visited = true;

            current_location = nextLocation;
        }
        else
        {
            current_facing_dir_idx++;
            if (current_facing_dir_idx == 4)
            {
                current_facing_dir_idx = 0;
            }
        }
    }

    for (size_t y = 0; y < cordinates.size(); y++)
    {
        for (size_t x = 0; x < cordinates[y].size(); x++)
        {
            if (cordinates[y][x].visited)
            {
                total++;
            }
        }
    }

    std::cout << "Visited: " << total << std::endl;
}