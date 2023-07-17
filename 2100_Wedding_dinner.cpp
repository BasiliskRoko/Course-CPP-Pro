/*----------------------------------------------------------------------
2100. Свадебный обед
https://acm.timus.ru/problem.aspx?space=1&num=2100
------------------------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

int main(int, char *[])
{

    int count;
    std::cin >> count;
    int iDinner = 2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (auto i = 0; i < count; i++)
    {
        std::string str;
        std::getline(std::cin, str);
        iDinner++;
        if (str.find("+one") != std::string::npos)
            iDinner++;
    }

    if (iDinner == 13)
        iDinner++;

    std::cout << iDinner * 100 << std::endl;
    return 0;
}