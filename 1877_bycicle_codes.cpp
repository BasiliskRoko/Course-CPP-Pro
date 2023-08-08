/*
1877. Велосипедные коды
https://acm.timus.ru/problem.aspx?space=1&num=1877
*/
#include <iostream>

int main(int, char *[])
{
    int code1, code2;
    std::cin >> code1;
    std::cin >> code2;

    auto modCode1 = code1 % 2;
    auto modCode2 = code2 % 2;

    if (modCode1 == 1 && modCode2 == 0)
    {
        std::cout << "no" << std::endl;
    }
    else
    {
        std::cout << "yes" << std::endl;
    }
    return 0;
}