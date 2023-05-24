#pragma once

#include "myiterator.h"
#include <algorithm>

template <class T, class A = std::allocator<T>>
class my_vector
{
    typedef typename std::allocator_traits<A>::template rebind_alloc<T> MyAlloc;
    typedef typename std::allocator_traits<A>::template rebind_traits<T> MyTraits;

    typedef MyIterator<T> iterator;
    typedef const MyIterator<T> const_iterator;
    typedef size_t size_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef T value_type;

public:
    my_vector(std::size_t _capacity = 1) : sz_capacity(_capacity)
    {
        T *newData = MyTraits::allocate(m_alloc, sz_capacity);
        std::swap(newData, data);
        MyTraits::deallocate(m_alloc, newData, sz_capacity);
    }
    void push_back(T &x)
    {
        if (sz_size == sz_capacity)
        {
            decltype(sz_capacity) newCapacity = sz_capacity * 2 + 1;
            T *newData = MyTraits::allocate(m_alloc, newCapacity);
            std::memcpy(newData, data, sz_capacity * sizeof(T)); // naive
            std::swap(newData, data);
            MyTraits::deallocate(m_alloc, newData, sz_capacity);
            sz_capacity = newCapacity;
        }

        MyTraits::construct(m_alloc, data + sz_size, x);
        ++sz_size;
    }

    // итераторы начала и конца контейнера
    MyIterator<T> begin() const
    {
        return MyIterator<T>(data);
    }
    MyIterator<T> end() const
    {
        return MyIterator<T>(data + sz_size);
    }

    size_t size() const
    {
        return sz_size;
    };

    size_t capacity() const
    {
        return sz_capacity;
    };

    bool empty() const
    {
        return sz_size == 0;
    };

private:
    std::size_t sz_size = 0;
    std::size_t sz_capacity = 0;
    T *data = nullptr;

    MyAlloc m_alloc;
};