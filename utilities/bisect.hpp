#ifndef M1UNE_BISECT_HPP
#define M1UNE_BISECT_HPP 1

#include <numeric>

namespace m1une {
namespace utilities {

template <typename F>
long long first_true(long long ng, long long ok, F pred) {
    auto distance = [](long long a, long long b) {
        return a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b) - a;
    };
    while (distance(ng, ok) > 1) {
        long long mid = std::midpoint(ng, ok);
        if (pred(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

template <typename F>
long long last_true(long long ok, long long ng, F pred) {
    auto distance = [](long long a, long long b) {
        return a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b) - a;
    };
    while (distance(ok, ng) > 1) {
        long long mid = std::midpoint(ok, ng);
        if (pred(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

template <typename F>
double real_first_true(double ng, double ok, F pred, int iterations = 80) {
    for (int i = 0; i < iterations; ++i) {
        double mid = (ng + ok) / 2.0;
        if (pred(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_BISECT_HPP
