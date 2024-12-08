#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// trim from start (in place)
inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void PrintVector(const std::vector<char> vec)
{
    std::cout << "[ ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "]";
}

std::vector<std::vector<char>>
GenerateCombis(int number, const std::vector<char> eqns, std::vector<std::vector<char>> curr_chars)
{

    int total_combis = number * number;
    if (curr_chars.size() > total_combis)
    {
        return curr_chars;
    }

    number -= 1;

    if (curr_chars.size() == 0)
    {
        for (size_t j = 0; j < eqns.size(); j++)
        {
            char curr_eqn = eqns[j];
            std::vector<char> tmp_chars;
            tmp_chars.push_back(curr_eqn);
            curr_chars.push_back(tmp_chars);
        }
    }

    for (size_t j = 0; j < eqns.size(); j++)
    {
        char curr_eqn = eqns[j];

        std::vector<std::vector<char>> tmp_chars = GenerateCombis(number, eqns, curr_chars);

        for (size_t i = 0; i < tmp_chars.size(); i++)
        {
            tmp_chars[i].push_back(curr_eqn);
            // PrintVector(tmp_chars[i]);
            curr_chars.push_back(tmp_chars[i]);
        }

        std::cout << std::endl;
    }
    return GenerateCombis(number, eqns, curr_chars);
    //
}

bool evaluate(const std::vector<int> numbers, int target_num)
{
    std::vector<char> eqns;
    eqns.push_back('+');
    eqns.push_back('*');
    std::vector<std::vector<char>> curr_chars;

    // Generate all possible combis, one less than numbers.size()
    std::vector<std::vector<char>> result = GenerateCombis(4, eqns, curr_chars);

    for (size_t i = 0; i < result.size(); i++)
    {

        PrintVector(result[i]);
    }

    return false;
}

int main()
{
    std::ifstream input("example.txt");

    std::string line;

    bool isRules = true;
    while (std::getline(input, line))
    {

        std::vector<std::string> split_res = split(line, ':');

        std::cout << split_res[0] << ": ";
        trim(split_res[0]);
        int target_number = std::stoi(split_res[0]);

        std::vector<int> eqn_numbers;
        std::vector<std::string> numbers = split(split_res[1], ' ');

        for (size_t i = 0; i < numbers.size(); i++)
        {
            trim(numbers[i]);
            if (numbers[i] == "")
            {
                continue;
            }
            std::cout << std::stoi(numbers[i]) << " ";
            eqn_numbers.push_back(std::stoi(numbers[i]));
        }
        evaluate(eqn_numbers, target_number);
        std::cout << std::endl;
    }
    return 0;
}
