
#include "lib.h"

#include <iostream>

#include <cstring>
#include <map>
#include <algorithm>
#include "myvector.h"

void work_with_map_n_allocator(size_t _size)
{
    using MapWithAlloc = std::map<int, int, std::less<int>, std_11_simple_allocator<std::pair<const int, int>>>;
    MapWithAlloc m(_size);

    for (int index = 0; index < 10; ++index)
    {
        m.insert({index, factorial<decltype(index)>(index)});
    }

    std::for_each(m.begin(), m.end(), [](auto &res)
                  { std::cout << res.first << " " << res.second << std::endl; });
}

void work_with_my_vector_n_allocator(size_t _size)
{
    my_vector<int, std_11_simple_allocator<int>> vec(_size);
    for (int index = 0; index < 10; ++index)
    {
        vec.push_back(index);
    }

    std::for_each(vec.begin(), vec.end(), [](auto &res)
                  { std::cout << res << std::endl; });
}

void work_with_my_vector(size_t _size)
{
    my_vector<int> vec(_size);
    for (int index = 0; index < 10; ++index)
    {
        vec.push_back(index);
    }

    std::for_each(vec.begin(), vec.end(), [](auto &res)
                  { std::cout << res << std::endl; });
}
int main(int, char const **)
{

    work_with_map_n_allocator(5);
    work_with_my_vector(3);
    work_with_my_vector_n_allocator(3);

    return 0;
}