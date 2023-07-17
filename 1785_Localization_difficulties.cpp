/*----------------------------------------------------------------------
1785. Трудности локализации
https://acm.timus.ru/problem.aspx?space=1&num=1785
------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <algorithm>

struct countMonsters
{
    countMonsters(int _count, std::string _name) : count(_count), name(_name){};

    int count;
    std::string name;
};
int main(int, char *[])
{
    std::vector<countMonsters> tableMonsters;

    tableMonsters.push_back(countMonsters(1, "few"));
    tableMonsters.push_back(countMonsters(5, "several"));
    tableMonsters.push_back(countMonsters(10, "pack"));
    tableMonsters.push_back(countMonsters(20, "lots"));
    tableMonsters.push_back(countMonsters(50, "horde"));
    tableMonsters.push_back(countMonsters(100, "throng"));
    tableMonsters.push_back(countMonsters(250, "swarm"));
    tableMonsters.push_back(countMonsters(500, "zounds"));
    tableMonsters.push_back(countMonsters(1000, "legion"));

    countMonsters res(-1, "");

    int N;
    std::cin >> N;

    std::find_if(tableMonsters.begin(), tableMonsters.end(), [&res, &N](auto i)
                 {
        if (i.count > N)
        {
            return true;
        }
        res = i;
        return false; });

    std::cout << res.name << std::endl;

    return 0;
}