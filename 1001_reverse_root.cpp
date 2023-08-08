/*----------------------------------------------------------------------
1001. Обратный корень
https://acm.timus.ru/problem.aspx?space=1&num=1001
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

    std::vector<double> numbers;
    std::string str;
    while (std::getline(std::cin, str))
    {
        std::stringstream ss(str);
        auto start = std::istream_iterator<double>{ss};

        auto end = std::istream_iterator<double>{};
        std::vector<double> numberInLine(start, end);
        std::copy(numberInLine.begin(), numberInLine.end(), std::back_inserter(numbers));
    }

    std::cout.precision(4);
    std::for_each(numbers.rbegin(), numbers.rend(), [](auto &i)
                  { std::cout << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(4) << std::sqrt(i) << std::endl; });

    return 0;
}