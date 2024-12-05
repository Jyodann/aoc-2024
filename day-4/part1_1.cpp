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

            if (curr_cord.character == 'X')
            {
                for (size_t o = 0; o < 8; o++)
                {
                    Cords offset = Offsets[o];

                    char charToComp = 'X';
                    Cords cords_with_offset = {
                        curr_cord.x + offset.x,
                        curr_cord.y + offset.y,
                        '-'};
                    for (size_t c = 0; c < 3; c++)
                    {
                        charToComp = Chars[c];

                        if (cords_with_offset.x < 0 || cords_with_offset.x > cordinates[y].size() - 1)
                        {
                            continue;
                        }

                        if (cords_with_offset.y < 0 || cords_with_offset.y > cordinates.size() - 1)
                        {
                            continue;
                        }

                        Cords offset_cord_info = cordinates[cords_with_offset.y][cords_with_offset.x];
                        if (offset_cord_info.character == charToComp)
                        {
                            cords_with_offset = {cords_with_offset.x + offset.x, cords_with_offset.y + offset.y, ' '};

                            if (offset_cord_info.character == 'S')
                            {
                                PrintCords(offset_cord_info);
                                times++;
                                std::cout << std::endl;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
        std::cout << times << std::endl;
    }

    return 0;
}
