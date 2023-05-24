#include "lib.h"

template <class T>
template <class U>
std_11_simple_allocator<T>::std_11_simple_allocator(const std_11_simple_allocator<U> &) noexcept
{
    array_pull.push_back(nullptr);
    array_pull.back().reset(reinterpret_cast<T *>(::operator new(PoolSize * sizeof(T))));
    array_size.push_back(std::make_pair(PoolSize, usedIndex(PoolSize, 0)));
}
