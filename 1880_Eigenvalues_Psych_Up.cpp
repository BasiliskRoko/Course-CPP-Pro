/*----------------------------------------------------------------------
1880. Собственные числа Psych Up
https://acm.timus.ru/problem.aspx?space=1&num=1880
------------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iomanip>

int main(int, char *[])
{

    std::vector<int> numbers[3];

    for (auto i = 0; i < 3; i++)
    {
        size_t count;
        std::cin >> count;

        std::string str;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, str);
        std::stringstream ss(str);
        auto start = std::istream_iterator<int>{ss};
        auto end = std::istream_iterator<int>{};
        std::vector<int> numberInLine(start, end);
        std::vector<int>::iterator endNumberInLine = numberInLine.end();
        if (numberInLine.size() > count)
            endNumberInLine = numberInLine.begin() + count;
        std::copy(numberInLine.begin(), endNumberInLine, std::back_inserter(numbers[i]));
    }

    std::vector<int> v_intersection01, v_intersection;

    std::set_intersection(numbers[0].begin(), numbers[0].end(), numbers[1].begin(), numbers[1].end(),
                          std::back_inserter(v_intersection01));

    std::set_intersection(v_intersection01.begin(), v_intersection01.end(), numbers[2].begin(), numbers[2].end(),
                          std::back_inserter(v_intersection));

    std::cout << v_intersection.size() << std::endl;

    return 0;
}