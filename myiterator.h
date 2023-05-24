
#pragma once
#include <iterator>

template <typename T>
struct MyIterator
{
    using self_type = MyIterator;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using reference = T &;

    MyIterator(pointer ptr) noexcept
        : _ptr{ptr}
    {
    }

    reference operator*() noexcept { return *_ptr; }
    pointer operator->() noexcept { return _ptr; }

    self_type operator++() noexcept
    {
        ++_ptr;
        return *this;
    }
    self_type operator++(int) noexcept
    {
        self_type tmp = *this;
        ++_ptr;
        return tmp;
    }

    self_type operator--() noexcept
    {
        --_ptr;
        return *this;
    }
    self_type operator--(int) noexcept
    {
        self_type tmp = *this;
        --_ptr;
        return tmp;
    }

    bool operator==(const self_type &other) const noexcept { return _ptr == other._ptr; }
    bool operator!=(const self_type &other) const noexcept { return _ptr != other._ptr; }

private:
    pointer _ptr;
};
