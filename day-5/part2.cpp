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

void PrintRule(const Rule rule)
{
    std::cout << rule.LeftNo << "|" << rule.RightNo << " ";
}

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
    int total = 0;
    std::ifstream input("input.txt");

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

        if (perfectNo != numbers.size())
        {
            std::cout << "Non Perfect Match: " << line << std::endl;
            int *arr = new int[numbers.size()];
            for (size_t i = 0; i < numbers.size(); i++)
            {
                int curr_no = numbers[i];
                int rules_matched = 0;
                std::vector<Rule> number_rules;
                for (size_t r = 0; r < rules.size(); r++)
                {
                    Rule rule = rules[r];
                    if (rule.LeftNo == curr_no)
                    {
                        number_rules.push_back(rule);
                    }
                }

                for (size_t r = 0; r < number_rules.size(); r++)
                {
                    Rule rule = number_rules[r];

                    for (size_t n = 0; n < numbers.size(); n++)
                    {
                        int num_to_find = numbers[n];

                        if (rule.RightNo == num_to_find)
                        {
                            rules_matched++;
                        }
                    }
                }

                // std::cout << std::endl;

                arr[numbers.size() - 1 - rules_matched] = curr_no;
            }

            std::cout << arr[numbers.size() / 2] << std::endl;
            total += arr[numbers.size() / 2];
            delete arr;
        }
    }

    std::cout << "Total: " << total << std::endl;
}