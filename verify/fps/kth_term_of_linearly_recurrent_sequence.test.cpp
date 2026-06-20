#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <cstdint>
#include <iostream>
#include <vector>

#include "../../fps/linear_recurrence.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int order;
    uint64_t index;
    std::cin >> order >> index;
    std::vector<mint> initial(order), recurrence(order);
    for (mint& value : initial) std::cin >> value;
    for (mint& value : recurrence) std::cin >> value;
    std::cout << m1une::fps::linear_recurrence_kth(initial, recurrence, index) << '\n';
}
