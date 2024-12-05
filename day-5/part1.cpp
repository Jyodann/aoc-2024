#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

struct Rule
{
    int LeftNo;
    int RightNo;
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

int main()
{
    std::ifstream input("example.txt");

    std::string line;
    std::vector<Rule> rules;
    bool isRules = true;
    while (std::getline(input, line))
    {
        if (line == "")
        {
            break;
        }
        if (isRules)
        {
            Rule rule = {
                std::stoi(line.substr(0, 2)),
                std::stoi(line.substr(3, 5))};
            rules.push_back(rule);
        }
    }

    while (std::getline(input, line))
    {
        std::vector<int> numbers = split(line, ',');
        int perfectNo = 0;
        for (size_t i = 0; i < numbers.size(); i++)
        {
            int currently_checked_number = numbers[i];
            // std::cout << "Checking: " << currently_checked_number << " ";
            // std::cout << "Size: " << numbers.size() << std::endl;
            int matched_rules = 0;
            for (int j = i - 1; j >= 0; j--)
            {
                // Check Backwards:
                int curr_backed_no = numbers[j];
                // std::cout << "Checking Backwards: " << numbers[j] << " ";

                for (size_t r = 0; r < rules.size(); r++)
                {
                    Rule rule = rules[r];

                    if (rule.RightNo == currently_checked_number)
                    {
                        if (rule.LeftNo == curr_backed_no)
                        {
                            matched_rules++;
                        }
                    }
                }
            }

            for (size_t j = i + 1; j < numbers.size(); j++)
            {
                // Check forwards:
                int curr_backed_no = numbers[j];
                // std::cout << "Checking Forwards: " << numbers[j] << " ";

                for (size_t r = 0; r < rules.size(); r++)
                {
                    Rule rule = rules[r];

                    if (rule.LeftNo == currently_checked_number)
                    {
                        if (rule.RightNo == curr_backed_no)
                        {
                            matched_rules++;
                        }
                    }
                }
            }

            if (matched_rules == numbers.size() - 1)
            {
                // std::cout << "Pefect Match" << std::endl;
                perfectNo++;
            }
        }

        if (perfectNo == numbers.size())
        {
            std::cout << "Perfect Match: " << line << std::endl;
        }
    }
}