#pragma once

template <class T>
struct std_11_simple_allocator
{
    using value_type = T;

    std::vector<std::shared_ptr<void>> array_pull;
    using usedIndex = std::vector<int>;
    using arrayPool = std::pair<std::size_t, usedIndex>;

    std::vector<arrayPool> array_size;
    std::size_t PoolSize = 5;
    std::size_t PoolIncrement = 1;

    std_11_simple_allocator() = default;

    std_11_simple_allocator(size_t _increment) noexcept : PoolIncrement(_increment){};

    template <class U>
    std_11_simple_allocator(const std_11_simple_allocator<U> &a) noexcept
    {
        PoolSize = a.PoolSize;
        PoolIncrement = a.PoolIncrement;
        array_pull.push_back(nullptr);
        array_pull.back().reset(reinterpret_cast<T *>(::operator new(PoolSize * sizeof(T))));
        array_size.push_back(std::make_pair(PoolSize, usedIndex(PoolSize, 0)));
    }

    T *allocate(std::size_t n)
    {
        T *res = nullptr;

        decltype(PoolSize) indexArray = 0;

        decltype(PoolSize) begin = PoolSize;
        decltype(begin) end = 0;

        for (auto &ptr : array_pull)
        {
            auto *beginPtr = reinterpret_cast<T *>(ptr.get());

            if (res != nullptr)
            {
                break;
            }

            for (decltype(indexArray) index = 0; index < array_size.at(indexArray).first; ++index)
            {
                if (res != nullptr)
                {

                    if (end == begin + n)
                    {
                        break;
                    }
                    else if (array_size.at(indexArray).second.at(index) != 0)
                    {
                        res = nullptr;
                        begin = array_size.at(indexArray).first;
                    }
                    else
                    {
                        end++;
                    }
                }
                else if (array_size.at(indexArray).second.at(index) == 0)
                {
                    res = beginPtr + index;
                    begin = index;
                    end = begin + 1;
                }
            }
            if (end != begin + n)
            {
                res = nullptr;
            }
            else
                break;
            indexArray++;
        }

        if (res == nullptr)
        {
            auto newPoolSize = PoolSize + array_size.size() * std::max(PoolIncrement, n);
            array_pull.push_back(nullptr);
            array_pull.back().reset(reinterpret_cast<T *>(::operator new(newPoolSize * sizeof(T))));
            array_size.push_back(std::make_pair(newPoolSize, usedIndex(newPoolSize, 0)));
            PoolSize = newPoolSize;
            res = reinterpret_cast<T *>(array_pull.back().get());
            begin = 0;
            end = begin + n;
        }

        for (decltype(n) set_i = begin; set_i < begin + n; ++set_i)
        {
            array_size.at(indexArray).second.at(set_i) = 1;
        }

        return res;
    };
    void deallocate(T *p, std::size_t n)
    {
        if (p == nullptr)
            return;
        decltype(PoolSize) indexArray = 0;
        for (auto &ptr : array_pull)
        {
            auto *beginPtr = reinterpret_cast<T *>(ptr.get());
            for (decltype(n) get_i = 0; get_i < array_size.at(indexArray).first; ++get_i)
            {
                if ((beginPtr + get_i) == p)
                {
                    for (auto reset_i = get_i; reset_i < get_i + n; ++reset_i)
                    {
                        array_size.at(indexArray).second.at(reset_i) = 0;
                    }
                    break;
                }
            }
            indexArray++;
        }
    };
};

template <class T, class U>
constexpr bool operator==(const std_11_simple_allocator<T> &a1, const std_11_simple_allocator<U> &a2) noexcept
{
    return true;
}

template <class T, class U>
constexpr bool operator!=(const std_11_simple_allocator<T> &a1, const std_11_simple_allocator<U> &a2) noexcept
{
    return false;
}
