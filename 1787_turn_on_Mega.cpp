/*----------------------------------------------------------------------
1787. Поворот на МЕГУ
https://acm.timus.ru/problem.aspx?space=1&num=1787
------------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

int main(int, char *[])
{
    int turnInMinuts, countMinuts;
    std::cin >> turnInMinuts >> countMinuts;

    std::string str;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, str);
    std::stringstream ss(str);
    auto start = std::istream_iterator<int>{ss};

    auto end = std::istream_iterator<int>{};
    std::vector<int> carInMinuts(start, end);

    carInMinuts.erase(carInMinuts.begin() + countMinuts, carInMinuts.end());

    decltype(turnInMinuts) jams = 0;
    std::for_each(carInMinuts.begin(), carInMinuts.end(), [&jams, &turnInMinuts](auto &i)
                  { jams += i - turnInMinuts; jams = std::max(jams, 0); });

    std::cout << jams << std::endl;

    return 0;
}