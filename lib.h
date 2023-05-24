#pragma once

#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>
#include "myiterator.h"
#include "simple_allocator.h"

#define UNUSED(variable) (void)variable

int version();

template <typename T>
T factorial(T &n)
{
    T f = 1;
    for (T i = 1; i <= n; ++i)
        f *= i;
    return f;
};
