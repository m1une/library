#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <cstdint>
#include <iostream>
#include <vector>

#include "../../utilities/fast_io.hpp"
#include "../../fps/linear_recurrence.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int order;
    uint64_t index;
    input.read(order, index);
    std::vector<mint> initial(order), recurrence(order);
    input.read(initial);
    input.read(recurrence);
    output.println(m1une::fps::linear_recurrence_kth(initial, recurrence, index));
}
