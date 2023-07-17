/*----------------------------------------------------------------------
1777. Племя аниндилъяква
https://acm.timus.ru/problem.aspx?space=1&num=1777
------------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

int main(int, char *[])
{

    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    auto start = std::istream_iterator<unsigned long long>{ss};

    auto end = std::istream_iterator<unsigned long long>{};
    std::vector<unsigned long long> heaps(start, end);
    unsigned long long quastion = 1;
    while (true)
    {
        std::sort(heaps.begin(), heaps.end());

        auto itEqual = std::find_if(heaps.begin() + 1, heaps.end(), [z = heaps.at(0)](auto h) mutable -> unsigned long long
                                    {
            if (h - z == 0)
            {
                return true;
            }
            else
            {
                z = h;
            }
            return false; });
        if (itEqual != heaps.end())
            break;

        decltype(quastion) diff = std::numeric_limits<unsigned long long>::max();
        auto prev = heaps.at(0);
        std::for_each(
            heaps.begin() + 1, heaps.end(), [&diff, &prev](auto &h)
            { if(h-prev<diff) diff=h-prev; prev = h; });
        heaps.push_back(diff);
        quastion++;
    }

    std::cout << quastion << std::endl;

    return 0;
}