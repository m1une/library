#ifndef M1UNE_FPS_LAGRANGE_INVERSION_HPP
#define M1UNE_FPS_LAGRANGE_INVERSION_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

template <class Mint>
Mint lagrange_inversion_coefficient(const FormalPowerSeries<Mint>& phi, int degree) {
    assert(1 <= degree && uint32_t(degree) < Mint::mod());
    assert(!phi.empty() && phi[0] != Mint(0));

    FormalPowerSeries<Mint> power = phi.pre(degree).pow(degree, degree);
    return power[degree - 1] / Mint(degree);
}

template <class Mint>
Mint lagrange_burmann_coefficient(const FormalPowerSeries<Mint>& phi,
                                  const FormalPowerSeries<Mint>& outer, int degree) {
    assert(0 <= degree && uint32_t(degree) < Mint::mod());
    if (degree == 0) return outer.empty() ? Mint(0) : outer[0];
    assert(!phi.empty() && phi[0] != Mint(0));

    FormalPowerSeries<Mint> power = phi.pre(degree).pow(degree, degree);
    Mint result = 0;
    int limit = std::min(degree, int(outer.size()) - 1);
    for (int i = 1; i <= limit; i++) {
        result += Mint(i) * outer[i] * power[degree - i];
    }
    return result / Mint(degree);
}

template <class Mint>
Mint compositional_inverse_coefficient(const FormalPowerSeries<Mint>& f, int degree) {
    assert(0 <= degree && uint32_t(degree) < Mint::mod());
    assert(2 <= int(f.size()) && f[0] == Mint(0) && f[1] != Mint(0));
    if (degree == 0) return Mint(0);

    FormalPowerSeries<Mint> divided(degree);
    for (int i = 0; i < degree && i + 1 < int(f.size()); i++) divided[i] = f[i + 1];
    FormalPowerSeries<Mint> phi = divided.inv(degree);
    return lagrange_inversion_coefficient(phi, degree);
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_LAGRANGE_INVERSION_HPP
