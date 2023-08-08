/*----------------------------------------------------------------------
2001. Математики и ягоды
https://acm.timus.ru/problem.aspx?space=1&num=2001
------------------------------------------------------------------------*/

#include <iostream>

int main(int, char *[])
{
    int maths[3][2];
    std::cin >> maths[0][0] >> maths[0][1];
    std::cin >> maths[1][0] >> maths[1][1];
    std::cin >> maths[2][0] >> maths[2][1];

    std::cout << maths[0][0] - maths[2][0] << " " << maths[0][1] - maths[1][1] << std::endl;

    return 0;
}