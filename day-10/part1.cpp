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
    int number;
};

void PrintCord(const Cords cord)
{
    std::cout << "(" << cord.x << "," << cord.y << ") - " << cord.number << " ";
}

const Cords directions[] = {
    {0, -1, false, 'u'},
    {1, 0, false, 'r'},
    {0, 1, false, 'd'},
    {-1, 0, false, 'l'},
};

void ResetCords(std::vector<std::vector<Cords>> &cordinates)
{
    for (size_t y = 0; y < cordinates.size(); y++)
    {
        for (size_t x = 0; x < cordinates[y].size(); x++)
        {
            cordinates[y][x].visited = false;
        }
    }
}

std::vector<Cords> FindPeak(const Cords cord,
                            std::vector<std::vector<Cords>> &cordinates,

                            int find_num)
{
    std::vector<Cords> paths;
    cordinates[cord.y][cord.x].visited = true;

    for (size_t i = 0; i < 4; i++)
    {
        Cords direction = directions[i];
        Cords new_cord = {
            cord.x + direction.x,
            cord.y + direction.y,
            false,
            '-'};
        if (new_cord.x < 0 || new_cord.x > cordinates[0].size() - 1)
        {
            continue;
        }

        if (new_cord.y < 0 || new_cord.y > cordinates.size() - 1)
        {
            continue;
        }

        new_cord = cordinates[cord.y + direction.y][cord.x + direction.x];

        if (new_cord.number == find_num + 1)
        {
            paths.push_back(new_cord);
        }
    }

    return paths;
}

int main()
{
    int total = 0;
    std::ifstream input("example1.txt");

    std::string line;

    std::vector<std::vector<Cords>> cordinates;
    int y_cord = 0;
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
                    (line[x] - '0')};
            tempCords.push_back(curr_cord);
            // PrintCord(curr_cord);
        }
        cordinates.push_back(tempCords);
        std::cout << std::endl;
        y_cord++;
    }

    for (size_t y = 0; y < cordinates.size(); y++)
    {
        for (size_t x = 0; x < cordinates[y].size(); x++)
        {
            Cords curr_cord = cordinates[y][x];
            std::vector<Cords> paths;
            if (curr_cord.number == 0)
            {
                // PrintCord(curr_cord);
                ResetCords(cordinates);
                auto hello = FindPeak(curr_cord, cordinates, 0);

                for (size_t i = 0; i < hello.size(); i++)
                {
                    PrintCord(hello[i]);
                    FindPeak(hello[i], cordinates, 1);
                }
            }
        }
    }
}
