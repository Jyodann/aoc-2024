#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Cords
{
    int x;
    int y;
    char character;
};

const Cords Offsets[] = {
    {-1, -1, '.'}, {0, -1, '.'}, {1, -1, '.'}, {-1, 0, '.'}, {1, 0, '.'}, {-1, 1, '.'}, {0, 1, '.'}, {1, 1, '.'}};

const char Chars[] = {'M', 'A', 'S'};
void PrintCords(const Cords cord)
{
    std::cout << "(" << cord.x << "," << cord.y << ")" << " " << cord.character << " ";
}

char ReturnChar(const std::vector<std::vector<Cords>> cordinates, Cords cordsToCheck)
{
    if (cordsToCheck.x < 0 || cordsToCheck.x > cordinates[0].size() - 1)
    {
        return '\0';
    }

    if (cordsToCheck.y < 0 || cordsToCheck.y > cordinates.size() - 1)
    {
        return '\0';
    }

    return cordinates[cordsToCheck.y][cordsToCheck.x].character;
}

int main()
{
    int times = 0;
    std::ifstream input("input.txt");

    std::string line;

    std::vector<std::vector<Cords>> cordinates;

    int y_axis = 0;
    while (std::getline(input, line))
    {
        std::vector<Cords> newCharacters;

        for (size_t i = 0; i < line.size(); i++)
        {
            Cords cord = {
                (int)i, y_axis, line[i]};
            newCharacters.push_back(cord);
        }
        y_axis++;
        cordinates.push_back(newCharacters);
    }

    for (size_t y = 0; y < cordinates.size(); y++)
    {
        for (size_t x = 0; x < cordinates[y].size(); x++)
        {
            Cords curr_cord = cordinates[y][x];

            if ('A' == curr_cord.character)
            {
                int matches = 0;
                PrintCords(curr_cord);
                // Top Corner
                Cords topLeftCorner = {
                    curr_cord.x - 1,
                    curr_cord.y - 1,
                    '-'};

                Cords topRightCorner = {
                    curr_cord.x + 1,
                    curr_cord.y - 1,
                    '-'};

                Cords bottomLeftCorner = {
                    curr_cord.x - 1,
                    curr_cord.y + 1,
                    '-'};

                Cords bottomRightCorner = {
                    curr_cord.x + 1,
                    curr_cord.y + 1,
                    '-'};
                if (ReturnChar(cordinates, topLeftCorner) == 'M' && ReturnChar(cordinates, bottomRightCorner) == 'S')
                {
                    matches++;
                }

                if (ReturnChar(cordinates, topRightCorner) == 'M' && ReturnChar(cordinates, bottomLeftCorner) == 'S')
                {
                    matches++;
                }

                if (ReturnChar(cordinates, topLeftCorner) == 'S' && ReturnChar(cordinates, bottomRightCorner) == 'M')
                {
                    matches++;
                }

                if (ReturnChar(cordinates, topRightCorner) == 'S' && ReturnChar(cordinates, bottomLeftCorner) == 'M')
                {
                    matches++;
                }

                if (matches >= 2)
                {
                    times++;
                }
            }
        }
    }
    std::cout << "Times:" << times << std::endl;
    return 0;
}
