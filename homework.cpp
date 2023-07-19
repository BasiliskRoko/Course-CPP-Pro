
#include "lib.h"

#include <iostream>

#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

/// <summary>
/// Extract the byte representation of a structure from the memory stream.
/// </summary>
/// <typeparam name="T">The Type of the structure to extract from the memory stream.</typeparam>
/// <param name="offset">The location of the structure in the memory stream.</param>
/// <returns>The structure as byte span.</returns>
namespace impl
{
    template <typename Iterator>
    void print(Iterator begin, Iterator end, int)
    {

        Iterator it = begin;
        for (int i = 0; it != end && i < 3; it++, ++i)
            printf("%d.", *it);
        printf("%d", *(it));
        std::cout << std::endl;
    }

    template <typename T>
    void print(T begin, T end, char)
    {
        std::for_each(begin, end, [](auto v)
                      { printf("%c", v); });
        std::cout << std::endl;
    }

    int print(int i)
    {
        std::cout << i;
        return 0;
    }

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

    template <typename... T>
    void func(std::tuple<T...> t)
    {
        std::apply(HelperCallable(), t);
    };

    template <typename... T,
              typename std::enable_if<!std::is_integral<T...>::value>::type * = {}>
    void print_ip(T &&...a)
    {
        func(a...);
    }

    template <typename T>
    auto print_ip(T value,
                  typename std::enable_if<
                      !std::is_integral<T>::value>::type * = {}) -> decltype(value.clear())
    {
        print(value.begin(), value.end(), *value.begin());
    }

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

} // impl

template <typename T>
void print_ip(T value)
{
    impl::print_ip(value);
}

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