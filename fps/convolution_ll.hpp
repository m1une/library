#ifndef M1UNE_FPS_CONVOLUTION_LL_HPP
#define M1UNE_FPS_CONVOLUTION_LL_HPP 1

#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

#include "convolution.hpp"
#include "../math/modint.hpp"

namespace m1une {
namespace fps {

// Exact convolution of signed 64-bit coefficients.
// Every result coefficient must fit in long long.
inline std::vector<long long> convolution_ll(
    const std::vector<long long>& first,
    const std::vector<long long>& second
) {
    if (first.empty() || second.empty()) return {};
    std::size_t result_size = first.size() + second.size() - 1;
    assert(result_size <= (std::size_t(1) << 24));

    using Mint1 = math::ModInt<167772161>;
    using Mint2 = math::ModInt<469762049>;
    using Mint3 = math::ModInt<754974721>;

    auto convolve = [&]<class Mint>() {
        std::vector<Mint> converted_first(first.size());
        std::vector<Mint> converted_second(second.size());
        for (int index = 0; index < int(first.size()); index++) {
            converted_first[index] = Mint(first[index]);
        }
        for (int index = 0; index < int(second.size()); index++) {
            converted_second[index] = Mint(second[index]);
        }
        return convolution(converted_first, converted_second);
    };

    std::vector<Mint1> result1 = convolve.template operator()<Mint1>();
    std::vector<Mint2> result2 = convolve.template operator()<Mint2>();
    std::vector<Mint3> result3 = convolve.template operator()<Mint3>();

    static const std::uint64_t inverse_mod1_mod2 =
        Mint2(Mint1::mod()).inv().val();
    static const std::uint64_t mod1_mod2 =
        std::uint64_t(Mint1::mod()) * Mint2::mod();
    static const std::uint64_t inverse_mod1_mod2_mod3 =
        Mint3(mod1_mod2 % Mint3::mod()).inv().val();
    static const unsigned __int128 crt_modulus =
        static_cast<unsigned __int128>(mod1_mod2) * Mint3::mod();

    std::vector<long long> result(result_size);
    for (int index = 0; index < int(result_size); index++) {
        std::uint64_t residue1 = result1[index].val();
        std::uint64_t residue2 = result2[index].val();
        std::uint64_t residue3 = result3[index].val();

        std::uint64_t second_digit =
            (residue2 + Mint2::mod() - residue1 % Mint2::mod()) %
            Mint2::mod();
        second_digit = second_digit * inverse_mod1_mod2 % Mint2::mod();
        std::uint64_t first_two =
            residue1 + std::uint64_t(Mint1::mod()) * second_digit;

        std::uint64_t third_digit =
            (residue3 + Mint3::mod() - first_two % Mint3::mod()) %
            Mint3::mod();
        third_digit =
            third_digit * inverse_mod1_mod2_mod3 % Mint3::mod();

        unsigned __int128 reconstructed =
            first_two + static_cast<unsigned __int128>(mod1_mod2) * third_digit;
        __int128 centered = reconstructed <= crt_modulus / 2
                                ? static_cast<__int128>(reconstructed)
                                : -static_cast<__int128>(crt_modulus - reconstructed);
        assert(std::numeric_limits<long long>::min() <= centered);
        assert(centered <= std::numeric_limits<long long>::max());
        result[index] = static_cast<long long>(centered);
    }
    return result;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_CONVOLUTION_LL_HPP
