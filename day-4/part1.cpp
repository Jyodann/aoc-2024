#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Cord
{
    int x;
    int y;
};

const Cord Offsets[] = {
    {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

const char CharsToDetect[] = {'M', 'A', 'S'};

bool CheckChar(
    const std::vector<std::vector<char>> chars,
    const Cord origin,
    const Cord offset,
    const char checkingChar)
{
    int max_x = chars.size() - 1;
    int max_y = chars[0].size() - 1;

    const Cord new_cord = {
        origin.x + offset.x,
        origin.y + offset.y,
    };

    if (new_cord.x < 0 || new_cord.x > max_x)
    {
        return false;
    }

    if (new_cord.y < 0 || new_cord.y > max_y)
    {
        return false;
    }

    if (chars[new_cord.y][new_cord.x] == checkingChar)
    {
        return true;
    }

    return false;
}

int main()
{
    int foundTimes = 0;
    std::ifstream input("example.txt");

    std::string line;
    std::vector<std::vector<char>> characters;

    while (std::getline(input, line))
    {
        std::vector<char> newCharacters;

        for (size_t i = 0; i < line.size(); i++)
        {
            newCharacters.push_back(line[i]);
        }
        characters.push_back(newCharacters);
    }

    for (int y = 0; y < characters.size(); y++)
    {
        for (int x = 0; x < characters[y].size(); x++)
        {
            char curr_char = characters[x][y];
            Cord origin = {y, x};
            if (curr_char == 'X')
            {
                for (size_t k = 0; k < 8; k++)
                {
                    Cord offset = Offsets[k];
                    for (size_t l = 0; l < 2; l++)
                    {
                        char checking_char = CharsToDetect[l];

                        if (CheckChar(characters, origin, offset, checking_char))
                        {
                            origin = {origin.x + offset.x, origin.y + offset.y};
                            std::cout << "OriginPoint: " << origin.x << "," << origin.y << " ";
                            if (checking_char == 'S')
                            {
                                std::cout << "Found" << std::endl;
                                foundTimes++;
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
    }

    for (int y = 0; y < characters.size(); y++)
    {
        for (int x = 0; x < characters[y].size(); x++)
        {
            char curr_char = characters[x][y];
            Cord origin = {x, y};
            if (curr_char == 'X')
            {
                for (size_t k = 0; k < 8; k++)
                {
                    Cord offset = Offsets[k];
                    for (size_t l = 0; l < 2; l++)
                    {
                        char checking_char = CharsToDetect[l];

                        if (CheckChar(characters, origin, offset, checking_char))
                        {
                            origin = {origin.x + offset.x, origin.y + offset.y};
                            std::cout << "OriginPoint: " << origin.x << "," << origin.y << " ";
                            if (checking_char == 'S')
                            {
                                std::cout << "Found" << std::endl;
                                foundTimes++;
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
    }

    std::cout << "Found: " << foundTimes << std::endl;

    return 0;
}
