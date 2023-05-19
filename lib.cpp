#include "lib.h"

#include "version.h"

int version() {
    return PROJECT_VERSION_PATCH;
}

std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void printOn(VectorVectorString &ip_pool) {
    auto Noop = [](auto a) { UNUSED(a); return true; };
    printOn(ip_pool, Noop);
}

void sortIP(VectorVectorString &ip_pool, bool direction) {
    std::sort(ip_pool.begin(), ip_pool.end(), [drct = direction](auto a, auto b) {
        if (a.size() != b.size()) {
            return false;
        }
        auto ai = a.cbegin();
        auto bi = b.cbegin();
        for (; ai != a.cend(), bi != b.cend(); ++ai, ++bi) {
            auto iA = atoi(ai->c_str());
            auto iB = atoi(bi->c_str());
            if (iA > iB) {
                return (drct) ? false : true;
            } else if (iA < iB) {
                return (drct) ? true : false;
            }
        }
        return false;
    });
}

void filter(VectorVectorString &ip_pool, int first) {
    auto finder1 = [value = first](auto a) { return value == atoi(a.cbegin()->c_str()); };
    printOn(ip_pool, finder1);
}

void filter(VectorVectorString &ip_pool, int first, int second) {
    auto finder2 = [value1 = first, value2 = second](VectorString a) { return value1 == atoi(a.at(0).c_str()) && value2 == atoi(a.at(1).c_str()); };
    printOn(ip_pool, finder2);
}

void filter_any(VectorVectorString &ip_pool, int byte) {
    auto finder3 = [value = byte](auto a) {
        auto result = std::find_if(a.begin(), a.end(), [value](auto ip4) { return value == atoi(ip4.c_str()); });
        return result != a.end();
    };
    printOn(ip_pool, finder3);
}
