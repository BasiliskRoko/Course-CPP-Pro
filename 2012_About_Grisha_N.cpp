/*----------------------------------------------------------------------
2012. Про Гришу Н.
https://acm.timus.ru/problem.aspx?space=1&num=2012
------------------------------------------------------------------------*/

#include <iostream>

int main(int, char *[])
{

    int F;
    std::cin >> F;

    std::cout << (((4 * 60 / 45) >= (12 - F)) ? "YES" : "NO") << std::endl;

    return 0;
}