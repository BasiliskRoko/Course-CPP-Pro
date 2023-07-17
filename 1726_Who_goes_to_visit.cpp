/*----------------------------------------------------------------------
1726. Кто ходит в гости…
https://acm.timus.ru/problem.aspx?space=1&num=1726
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
    int count;
    std::cin >> count;

    std::vector<long long> X;
    std::vector<long long> Y;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (auto i = 0; i < count; i++)
    {
        std::string str;

        std::getline(std::cin, str);
        std::stringstream ss(str);
        auto start = std::istream_iterator<long long>{ss};
        auto end = std::istream_iterator<long long>{};
        std::vector<long long> member(start, end);

        X.push_back(member.at(0));
        Y.push_back(member.at(1));
    }

    std::sort(X.begin(), X.end());
    std::sort(Y.begin(), Y.end());

    auto sum = 0;
    for (auto member = 1; member < count; member++)
    {
        sum += (X.at(member) - X.at(member - 1)) * (member) * (count - member) * 2;
        sum += (Y.at(member) - Y.at(member - 1)) * (member) * (count - member) * 2;
    }

    std::cout << sum / (count * (count - 1)) << std::endl;

    return 0;
}