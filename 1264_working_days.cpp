/*----------------------------------------------------------------------
1264. Трудовые будни
https://acm.timus.ru/problem.aspx?space=1&num=1264
------------------------------------------------------------------------*/

#include <iostream>

int main(int, char *[])
{
    int sizeArray, Number;
    std::cin >> sizeArray >> Number;
    std::cout << sizeArray * (Number + 1) << std::endl;

    return 0;
}