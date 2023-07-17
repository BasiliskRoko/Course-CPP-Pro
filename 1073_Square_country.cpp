/*----------------------------------------------------------------------
1073. Квадратная страна
https://acm.timus.ru/problem.aspx?space=1&num=1073
------------------------------------------------------------------------*/

#include <iostream>
#include <cmath>

int main(int, char *[])
{

    int N;
    std::cin >> N;
    int countDeal = 0;
    int mul = 1;

    if (N / 2 + N / 2 == N)
    {
        N /= 2;
        mul = 2;
    }

    while (N)
    {
        N -= std::pow(static_cast<int>(std::trunc(std::sqrt(N))), 2);
        countDeal++;
    }
    std::cout << countDeal * mul << std::endl;

    return 0;
}