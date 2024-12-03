#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream input("input.txt");
    std::string line;
    std::string token = "mul(";
    std::string numeric_part_1, numeric_part_2;

    const char numeric_tokens[] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };

    std::vector<int> parsed_tokens;
    std::vector<int> temp_parsed_tokens;
    char curr_token;
    bool isNum = false;
    while (std::getline(input, line))
    {
        int res = 0;
        while ((res = line.find(token, res + 1)) != (int)std::string::npos)
        {
            numeric_part_1 = "";
            unsigned long tokenLoc = res + 4;
            while (tokenLoc < line.size())
            {
                curr_token = line[tokenLoc];

                tokenLoc++;

                for (size_t i = 0; i < 10; i++)
                {
                    if (numeric_tokens[i] == curr_token)
                    {
                        numeric_part_1 += curr_token;
                        isNum = true;
                        break;
                    }
                }

                if (curr_token == ',')
                {
                    temp_parsed_tokens.push_back(std::stoi(numeric_part_1));
                    numeric_part_1 = "";
                    continue;
                }

                if (curr_token == ')')
                {
                    parsed_tokens.push_back(temp_parsed_tokens[0]);
                    parsed_tokens.push_back(std::stoi(numeric_part_1));
                    temp_parsed_tokens.clear();
                    break;
                }

                if (isNum)
                {
                    isNum = false;
                    continue;
                }
                temp_parsed_tokens.clear();
                break;
            }
        }
    }
    int total = 0;
    for (size_t i = 0; i < parsed_tokens.size(); i += 2)
    {
        total += parsed_tokens[i] * parsed_tokens[i + 1];
    }

    std::cout << total << std::endl;

    input.close();
    return 0;
}
