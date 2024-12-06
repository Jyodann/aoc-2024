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

bool ExploreTillExhaust(int max_moves,
                        std::vector<std::vector<Cords>> map,
                        const Cords new_obstacle_location,
                        const Cords starting_location,
                        const Cords directions[])
{
    Cords direction;
    int moves = 0;
    int current_facing_dir_idx = 0;
    map[new_obstacle_location.y][new_obstacle_location.x].typeOfChar = '#';
    Cords nextLocation = starting_location, current_location = starting_location;
    max_moves = map.size() * map.size();
    while (moves != max_moves)
    {
        direction = directions[current_facing_dir_idx];
        int next_y = current_location.y + direction.y;
        int next_x = current_location.x + direction.x;

        if (next_y < 0 || next_y > map.size() - 1)
        {
            map[current_location.y][current_location.x].visited = true;
            return false;
        }

        if (next_x < 0 || next_x > map[0].size() - 1)
        {
            map[current_location.y][current_location.x].visited = true;
            return false;
        }
        nextLocation = map[next_y][next_x];
        // PrintCord(nextLocation);

        if (nextLocation.typeOfChar != '#')
        {
            map[current_location.y][current_location.x].visited = true;

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
        moves++;
    }

    std::cout << "Found Obstacle ";
    PrintCord(new_obstacle_location);
    std::cout << std::endl;
    return true;
}

int main()
{
    int found = 0;
    int total = 0;
    std::ifstream input("input.txt");

    std::string line;

    std::vector<std::vector<Cords>> completed_map_cords;
    std::vector<std::vector<Cords>> original_map;
    std::vector<Cords> all_possible_visit_areas;
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
        completed_map_cords.push_back(tempCords);
        original_map.push_back(tempCords);
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

        if (next_y < 0 || next_y > completed_map_cords.size() - 1)
        {
            completed_map_cords[current_location.y][current_location.x].visited = true;
            break;
        }

        if (next_x < 0 || next_x > completed_map_cords[0].size() - 1)
        {
            completed_map_cords[current_location.y][current_location.x].visited = true;
            break;
        }
        nextLocation = completed_map_cords[next_y][next_x];
        // PrintCord(nextLocation);

        if (nextLocation.typeOfChar != '#')
        {
            completed_map_cords[current_location.y][current_location.x].visited = true;

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

    for (size_t y = 0; y < completed_map_cords.size(); y++)
    {
        for (size_t x = 0; x < completed_map_cords[y].size(); x++)
        {
            if (completed_map_cords[y][x].visited)
            {
                all_possible_visit_areas.push_back(completed_map_cords[y][x]);
                total++;
            }
        }
    }

    for (size_t i = 0; i < all_possible_visit_areas.size(); i++)
    {

        for (size_t y = 0; y < original_map.size(); y++)
        {
            for (size_t x = 0; x < original_map[0].size(); x++)
            {
                completed_map_cords[y][x] = original_map[y][x];
            }
        }

        if (ExploreTillExhaust(
                completed_map_cords.size() * completed_map_cords.size(),
                completed_map_cords,
                all_possible_visit_areas[i],
                starting_pos,
                directions))
        {
            found++;
        };
    }
    std::cout << "Found " << found << std::endl;
    std::cout << "Visited: " << total << std::endl;
}