#include "lib.h"
/*
template <typename T>
MyIterator<T>::MyIterator() : current(0)
{
}

template <typename T>
MyIterator<T>::MyIterator(const MyIterator<T> &other) : current(other.current)
{
}

template <typename T>
MyIterator<T> &MyIterator<T>::operator=(const MyIterator<T> &other)
{
    // исключаем присваивание самому себе
    if (this != &other)
        current = other.current;

    return *this;
}

// постфиксная версия возвращает значение до инкремента
template <typename T>
MyIterator<T> MyIterator<T>::operator++(int)
{
    MyIterator<T> tmp(*this);
    operator++();
    return tmp;
}

template <typename T>
T *MyIterator<T>::operator->()
{
    return current;
}

template <typename T>
bool MyIterator<T>::operator==(const MyIterator<T> &other)
{
    return current == other.current;
}
*/