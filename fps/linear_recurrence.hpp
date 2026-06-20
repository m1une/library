#ifndef M1UNE_FPS_LINEAR_RECURRENCE_HPP
#define M1UNE_FPS_LINEAR_RECURRENCE_HPP 1

#include <cassert>
#include <cstdint>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

template <class Mint>
Mint coefficient_of_rational(FormalPowerSeries<Mint> numerator,
                             FormalPowerSeries<Mint> denominator, uint64_t index) {
    using Fps = FormalPowerSeries<Mint>;
    assert(!denominator.empty() && denominator[0] != Mint(0));

    while (index > 0) {
        Fps denominator_negative = denominator;
        for (int i = 1; i < int(denominator_negative.size()); i += 2) {
            denominator_negative[i] = Mint(0) - denominator_negative[i];
        }

        Fps numerator_product = numerator * denominator_negative;
        Fps denominator_product = denominator * denominator_negative;
        Fps next_numerator;
        Fps next_denominator;
        next_numerator.reserve((numerator_product.size() + 1) / 2);
        next_denominator.reserve((denominator_product.size() + 1) / 2);
        for (int i = int(index & 1); i < int(numerator_product.size()); i += 2) {
            next_numerator.emplace_back(numerator_product[i]);
        }
        for (int i = 0; i < int(denominator_product.size()); i += 2) {
            next_denominator.emplace_back(denominator_product[i]);
        }
        numerator = std::move(next_numerator);
        denominator = std::move(next_denominator);
        index >>= 1;
    }
    return numerator.empty() ? Mint(0) : numerator[0] / denominator[0];
}

template <class Mint>
Mint linear_recurrence_kth(const std::vector<Mint>& initial,
                           const std::vector<Mint>& recurrence, uint64_t index) {
    using Fps = FormalPowerSeries<Mint>;
    assert(!initial.empty() && initial.size() == recurrence.size());
    if (index < initial.size()) return initial[index];

    const int order = int(recurrence.size());
    Fps denominator(order + 1);
    denominator[0] = 1;
    for (int i = 0; i < order; i++) denominator[i + 1] = Mint(0) - recurrence[i];
    Fps numerator = (Fps(initial) * denominator).pre(order);
    return coefficient_of_rational(std::move(numerator), std::move(denominator), index);
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_LINEAR_RECURRENCE_HPP
