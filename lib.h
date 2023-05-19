#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#define UNUSED(variable) (void)variable

using VectorString = std::vector<std::string>;
using VecStrIter = VectorString::const_iterator;
using VectorVectorString = std::vector<VectorString>;
using VecVecStringIter = std::vector<VectorString>::const_iterator;
int version();

std::vector<std::string> split(const std::string &str, char d);

template <typename F>
void printOn(VectorVectorString &ip_pool, F &&func) {
    auto result = std::find_if(ip_pool.begin(), ip_pool.end(), func);

    while (result != ip_pool.end()) {
        for (auto ip_part = result->cbegin(); ip_part != result->cend(); ++ip_part) {
            if (ip_part != result->cbegin()) {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
        result = std::find_if(++result, ip_pool.end(), func);
    };
}

void printOn(VectorVectorString &ip_pool);

void sortIP(VectorVectorString &ip_pool, bool direction = true);

void filter(VectorVectorString &ip_pool, int first);
void filter(VectorVectorString &ip_pool, int first, int second);
void filter_any(VectorVectorString &ip_pool, int byte);
