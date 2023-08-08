/*----------------------------------------------------------------------
1197. Один в поле воин
https://acm.timus.ru/problem.aspx?space=1&num=1197
------------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <vector>

int main(int, char *[])
{
    std::vector<int> resultHits;
    std::vector<std::pair<int, int>> hitsHorse = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, -1}, {2, 1}, {1, -2}, {-1, -2}};
    int count;
    std::cin >> count;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (auto i = 0; i < count; i++)
    {
        std::string str;
        std::getline(std::cin, str);
        // a=97.. h =104
        int hor = (int)str.at(0);
        int vert = std::atoi(str.substr(1, 1).c_str());
        int hit = 0;
        std::for_each(hitsHorse.begin(), hitsHorse.end(), [&hor, &vert, &hit](auto &h)
                      {
            if(vert + h.second > 0 && vert + h.second <=8  && hor + h.first >= 97 && hor+h.first <= 104)
                hit++; });

        resultHits.push_back(hit);
    }

    std::for_each(resultHits.begin(), resultHits.end(), [](auto &h)
                  { std::cout << h << std::endl; });

    return 0;
}