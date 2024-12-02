#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool checkDifferenceSafe(int firstNum, int secondNum)
{
    if (abs(firstNum - secondNum) < 1 || abs(firstNum - secondNum) > 3)
    {
        return false;
    }
    return true;
}

bool checkIfDecreasing(int firstNum, int secondNum)
{
    if (firstNum - secondNum > 0)
    {
        return true;
    }
    return false;
}

bool checkIfSafe(const std::vector<int> vector)
{
    bool isSafe = true;
    int num, sec_num;
    bool isDecreasing = checkIfDecreasing(vector[0], vector[1]);

    for (size_t i = 0; i < vector.size() - 1; i++)
    {
        num = vector[i];
        sec_num = vector[i + 1];

        if (checkIfDecreasing(num, sec_num) != isDecreasing)
        {
            isSafe = false;
            break;
        }

        if (!checkDifferenceSafe(num, sec_num))
        {

            isSafe = false;
            break;
        }
    }

    return isSafe;
}

bool attemptErrorCorrection(std::vector<int> vector)
{
    std::vector<int> temp_vec;

    for (size_t i = 0; i < vector.size(); i++)
    {
        temp_vec.clear();
        for (size_t j = 0; j < vector.size(); j++)
        {
            if (j == i)
            {
                continue;
            }

            temp_vec.push_back(vector[j]);
        }

        if (checkIfSafe(temp_vec))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    std::string delim = " ";
    int safe_num = 0;

    std::vector<int> first_num_list;
    size_t pos;
    while (std::getline(input, line))
    {
        // std::cout << line << " : ";
        first_num_list.clear();
        while ((pos = line.find(delim)) != std::string::npos)
        {
            first_num_list.push_back(std::stoi(line.substr(0, pos)));
            line.erase(0, pos + delim.length());
        }

        first_num_list.push_back(std::stoi(line.substr(0, line.length())));
        // std::cout << checkIfSafe(first_num_list) << std::endl;

        if (checkIfSafe(first_num_list))
        {
            safe_num++;
            continue;
        }
        else
        {
            if (attemptErrorCorrection(first_num_list))
            {
                safe_num++;
            }
        }
    }

    std::cout << safe_num << std::endl;
    return 0;
}
