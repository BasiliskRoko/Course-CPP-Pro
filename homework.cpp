
/*!
\file
\brief файл домашнего задания
  
    \author Aleksei
    \version 1.0
    \date Июль 2023 года
    \warning Данный файл создан только в учебных целях

Данный файл содержит в себе функцию main и выполнение ДЗ
*/
#include "lib.h"

#include <iostream>

#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

/*!
Вывод контейнера int и то, что можно к нему не явно преобразовать. таким образом исключаем std::string
\param[in] begin Итератор начала
\param[in] end Итератор конца
\param[in] notused целочисленный аргумент

*/
template <typename Iterator>
void print(Iterator begin, Iterator end, int)
{
    Iterator it = begin;
    for (int i = 0; it != end; it++, ++i)
    {
        if (i > 0)
            std::cout << ".";
        std::cout << *it;
    }
    std::cout << std::endl;
}

/*!
Вывод контейнера char и то, что можно к нему не явно преобразовать. таким образом выводим std::string
\param[in] begin Итератор начала
\param[in] end Итератор конца
\param[in] notused целочисленный аргумент
*/
template <typename T>
void print(T begin, T end, char)
{
    std::for_each(begin, end, [](auto v)
                  { printf("%c", v); });
    std::cout << std::endl;
}

/*!
    \brief Объект для вывода кортежа через std::apply
*/
struct HelperCallable
{
    template <typename... Args>
    void operator()(const Args &...tupleArgs)
    {
        size_t index = 0;
        auto printElem = [&index](const auto &x)
        {
            if (index++ > 0)
                std::cout << ".";
            std::cout << x;
        };

        (printElem(tupleArgs), ...);
        std::cout << std::endl;
    }
};

/*!
Функция вывода tuple типа
\param[in] value значение
*/
template <typename... T,
          typename std::enable_if<!std::is_integral<T...>::value>::type * = {}>
void print_ip(T &&...value)
{
    std::apply(HelperCallable(), value...);
}

/*!
Функция вывода контейнерного типа
\param[in] value значение
*/
template <typename T>
auto print_ip(T value,
              typename std::enable_if<
                  !std::is_integral<T>::value>::type * = {}) -> decltype(value.clear())
{
    print(value.begin(), value.end(), *value.begin());
}

/*!
Функция вывода целочисленного типа и, что можно к нему не явно преобразовать в побайтовом виде
\param[in] value значение
*/
template <typename T>
void print_ip(T value,
              typename std::enable_if<
                  std::is_integral<T>::value>::type * = {})
{
    unsigned char *p = (unsigned char *)&value;
    size_t i;
    for (i = sizeof(T) - 1; i > 0; i--)
        printf("%d.", static_cast<int>(p[i]));
    printf("%d", static_cast<int>(p[i]));
    std::cout << std::endl;
}

/*!
Функция main
последовательно выполняем требуемые кейсы
\return 0
*/
int main(int, char const **)
{
    print_ip(int8_t{-1});                           // 255
    print_ip(int16_t{0});                           // 0.0
    print_ip(int32_t{2130706433});                  // 127.0.0.1
    print_ip(int64_t{8875824491850138409});         // 123.45.67.89.101.112.131.41
    print_ip(std::string{"Hello, World!"});         // Hello, World!
    print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    print_ip(std::make_tuple(123, 456, 789, 0));    // 123.456.789.0
    return 0;
}