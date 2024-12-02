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

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    std::string delim = " ";
    int num = 0, sec_num = 0, safe_num = 0;
    bool isDecreasing = false;
    bool isSafe = true;
    std::vector<int> first_num_list;
    size_t pos;
    while (std::getline(input, line))
    {
        isSafe = true;
        std::cout << line << " : ";
        first_num_list.clear();
        while ((pos = line.find(delim)) != std::string::npos)
        {
            first_num_list.push_back(std::stoi(line.substr(0, pos)));
            line.erase(0, pos + delim.length());
        }

        first_num_list.push_back(std::stoi(line.substr(0, line.length())));

        num = first_num_list[0];
        sec_num = first_num_list[1];

        // Check if decreasing or increasing:
        isDecreasing = checkIfDecreasing(num, sec_num);
        isSafe = checkDifferenceSafe(num, sec_num);
        for (size_t i = 1; i < first_num_list.size() - 1; i++)
        {
            num = first_num_list[i];
            sec_num = first_num_list[i + 1];

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
        std::cout << isSafe << std::endl;

        if (isSafe)
        {
            safe_num++;
        }
    }

    std::cout << safe_num << std::endl;
    return 0;
}
