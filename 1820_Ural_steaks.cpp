/*----------------------------------------------------------------------
1820. Уральские бифштексы
https://acm.timus.ru/problem.aspx?space=1&num=1820
------------------------------------------------------------------------*/

#include <iostream>
#include <cmath>
#include <algorithm>

int main(int, char *[])
{

    int N, K;
    std::cin >> N >> K;

    std::cout << std::max<int>(2, std::ceil(N * 2.0 / K)) << std::endl;

    return 0;
}