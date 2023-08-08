/*----------------------------------------------------------------------
2066. Простое выражение
https://acm.timus.ru/problem.aspx?space=1&num=2066
------------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(int, char *[])
{

    std::vector<int> numbers;

    for (auto i = 0; i < 3; i++)
    {
        std::string str;
        std::getline(std::cin, str);
        std::stringstream ss(str);
        auto start = std::istream_iterator<int>{ss};
        numbers.push_back(*start);
    }

    if (numbers[1] == 1 || numbers[2] == 1 || !(numbers[1] > 0 && numbers[2] > 0))
    {
        std::cout << numbers[0] - numbers[1] - numbers[2] << std::endl;
    }
    else
    {
        std::cout << numbers[0] - numbers[1] * numbers[2] << std::endl;
    }

    return 0;
}