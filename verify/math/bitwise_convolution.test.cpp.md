---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bitwise_convolution.hpp
    title: Bitwise Convolution
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_xor_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_xor_convolution
  bundledCode: "#line 1 \"verify/math/bitwise_convolution.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\n\n#line 1 \"math/bitwise_convolution.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"math/zeta_mobius_transform.hpp\"\n\n\n\n#line 7 \"math/zeta_mobius_transform.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail\
    \ {\n\ninline bool is_power_of_two(std::size_t size) noexcept {\n    return size\
    \ != 0 && (size & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
    \ limit) {\n    std::vector<std::size_t> primes;\n    std::vector<bool> is_prime(limit\
    \ + 1, true);\n    if (!is_prime.empty()) is_prime[0] = false;\n    if (limit\
    \ >= 1) is_prime[1] = false;\n    for (std::size_t value = 2; value <= limit;\
    \ ++value) {\n        if (!is_prime[value]) continue;\n        primes.emplace_back(value);\n\
    \        if (value > limit / value) continue;\n        for (\n            std::size_t\
    \ multiple = value * value;\n            multiple <= limit;\n            multiple\
    \ += value\n        ) {\n            is_prime[multiple] = false;\n        }\n\
    \    }\n    return primes;\n}\n\n}  // namespace zeta_mobius_transform_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n \
    \   for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 10 \"math/bitwise_convolution.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace bitwise_convolution_detail {\n\ninline std::size_t common_size(\n\
    \    std::size_t first_size,\n    std::size_t second_size\n) {\n    std::size_t\
    \ required = first_size > second_size\n        ? first_size\n        : second_size;\n\
    \    std::size_t size = 1;\n    while (size < required) size <<= 1;\n    return\
    \ size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n    std::vector<T>\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    return first;\n}\n\n}  // namespace bitwise_convolution_detail\n\
    \ntemplate <typename T>\nvoid walsh_hadamard_transform(\n    std::vector<T>& values,\n\
    \    bool inverse = false\n) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t length = 1; length < values.size(); length <<= 1) {\n  \
    \      for (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += length << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < length; ++offset) {\n                T first = values[block +\
    \ offset];\n                T second = values[block + offset + length];\n    \
    \            values[block + offset] = first + second;\n                values[block\
    \ + offset + length] = first - second;\n            }\n        }\n    }\n    if\
    \ (inverse) {\n        T size = T(static_cast<long long>(values.size()));\n  \
    \      for (T& value : values) value /= size;\n    }\n}\n\ntemplate <typename\
    \ T>\nstd::vector<T> bitwise_or_convolution(\n    std::vector<T> first,\n    std::vector<T>\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ size = bitwise_convolution_detail::common_size(\n        first.size(),\n   \
    \     second.size()\n    );\n    first.resize(size);\n    second.resize(size);\n\
    \    subset_zeta_transform(first);\n    subset_zeta_transform(second);\n    first\
    \ = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    subset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_and_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    superset_zeta_transform(first);\n    superset_zeta_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    superset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_xor_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    walsh_hadamard_transform(first);\n    walsh_hadamard_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    walsh_hadamard_transform(first, true);\n    return\
    \ first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n#line\
    \ 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t\
    \ Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus must be\
    \ positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static constexpr\
    \ uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr ModInt\
    \ raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n        return\
    \ x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class\
    \ Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr\
    \ ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 5 \"verify/math/bitwise_convolution.test.cpp\"\n\n#line 10\
    \ \"verify/math/bitwise_convolution.test.cpp\"\n\nnamespace {\n\nusing m1une::math::bitwise_and_convolution;\n\
    using m1une::math::bitwise_or_convolution;\nusing m1une::math::bitwise_xor_convolution;\n\
    \ntemplate <typename T, typename Operation>\nstd::vector<T> naive(\n    const\
    \ std::vector<T>& first,\n    const std::vector<T>& second,\n    Operation operation\n\
    ) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t size\
    \ = 1;\n    while (size < first.size() || size < second.size()) size <<= 1;\n\
    \    std::vector<T> result(size);\n    for (std::size_t i = 0; i < first.size();\
    \ ++i) {\n        for (std::size_t j = 0; j < second.size(); ++j) {\n        \
    \    result[operation(i, j)] += first[i] * second[j];\n        }\n    }\n    return\
    \ result;\n}\n\nvoid test_transforms() {\n    std::vector<long long> original{3,\
    \ -1, 4, 1, 5, -9, 2, 6};\n\n    std::vector<long long> values = original;\n \
    \   m1une::math::subset_zeta_transform(values);\n    m1une::math::subset_mobius_transform(values);\n\
    \    assert(values == original);\n\n    values = original;\n    m1une::math::superset_zeta_transform(values);\n\
    \    m1une::math::superset_mobius_transform(values);\n    assert(values == original);\n\
    \n    values = original;\n    m1une::math::walsh_hadamard_transform(values);\n\
    \    m1une::math::walsh_hadamard_transform(values, true);\n    assert(values ==\
    \ original);\n}\n\ntemplate <typename T>\nvoid check_convolutions(\n    const\
    \ std::vector<T>& first,\n    const std::vector<T>& second\n) {\n    assert(\n\
    \        bitwise_or_convolution(first, second) ==\n        naive(first, second,\
    \ [](std::size_t i, std::size_t j) {\n            return i | j;\n        })\n\
    \    );\n    assert(\n        bitwise_and_convolution(first, second) ==\n    \
    \    naive(first, second, [](std::size_t i, std::size_t j) {\n            return\
    \ i & j;\n        })\n    );\n    assert(\n        bitwise_xor_convolution(first,\
    \ second) ==\n        naive(first, second, [](std::size_t i, std::size_t j) {\n\
    \            return i ^ j;\n        })\n    );\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 0x1234fedcba98765ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ std::size_t first_size = random() % 18;\n        std::size_t second_size = random()\
    \ % 18;\n        std::vector<long long> first(first_size);\n        std::vector<long\
    \ long> second(second_size);\n        for (long long& value : first) {\n     \
    \       value = static_cast<long long>(random() % 21) - 10;\n        }\n     \
    \   for (long long& value : second) {\n            value = static_cast<long long>(random()\
    \ % 21) - 10;\n        }\n        check_convolutions(first, second);\n    }\n\
    }\n\nvoid test_modint() {\n    using mint = m1une::math::modint998244353;\n  \
    \  std::vector<mint> first;\n    std::vector<mint> second;\n    for (int value\
    \ = 0; value < 13; ++value) {\n        first.emplace_back(value * value - 7);\n\
    \    }\n    for (int value = 0; value < 9; ++value) {\n        second.emplace_back(value\
    \ * 3 + 1);\n    }\n    check_convolutions(first, second);\n}\n\n}  // namespace\n\
    \nint main() {\n    test_transforms();\n    test_randomized();\n    test_modint();\n\
    \n    int n;\n    std::cin >> n;\n    int size = 1 << n;\n    using mint = m1une::math::modint998244353;\n\
    \    std::vector<mint> a(size), b(size);\n    for (int i = 0; i < size; i++) {\n\
    \        long long x;\n        std::cin >> x;\n        a[i] = x;\n    }\n    for\
    \ (int i = 0; i < size; i++) {\n        long long x;\n        std::cin >> x;\n\
    \        b[i] = x;\n    }\n    std::vector<mint> c = bitwise_xor_convolution(a,\
    \ b);\n    for (int i = 0; i < size; i++) {\n        if (i) std::cout << ' ';\n\
    \        std::cout << c[i].val();\n    }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\
    \n\n#include \"../../math/bitwise_convolution.hpp\"\n#include \"../../math/modint.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \nnamespace {\n\nusing m1une::math::bitwise_and_convolution;\nusing m1une::math::bitwise_or_convolution;\n\
    using m1une::math::bitwise_xor_convolution;\n\ntemplate <typename T, typename\
    \ Operation>\nstd::vector<T> naive(\n    const std::vector<T>& first,\n    const\
    \ std::vector<T>& second,\n    Operation operation\n) {\n    if (first.empty()\
    \ || second.empty()) return {};\n    std::size_t size = 1;\n    while (size <\
    \ first.size() || size < second.size()) size <<= 1;\n    std::vector<T> result(size);\n\
    \    for (std::size_t i = 0; i < first.size(); ++i) {\n        for (std::size_t\
    \ j = 0; j < second.size(); ++j) {\n            result[operation(i, j)] += first[i]\
    \ * second[j];\n        }\n    }\n    return result;\n}\n\nvoid test_transforms()\
    \ {\n    std::vector<long long> original{3, -1, 4, 1, 5, -9, 2, 6};\n\n    std::vector<long\
    \ long> values = original;\n    m1une::math::subset_zeta_transform(values);\n\
    \    m1une::math::subset_mobius_transform(values);\n    assert(values == original);\n\
    \n    values = original;\n    m1une::math::superset_zeta_transform(values);\n\
    \    m1une::math::superset_mobius_transform(values);\n    assert(values == original);\n\
    \n    values = original;\n    m1une::math::walsh_hadamard_transform(values);\n\
    \    m1une::math::walsh_hadamard_transform(values, true);\n    assert(values ==\
    \ original);\n}\n\ntemplate <typename T>\nvoid check_convolutions(\n    const\
    \ std::vector<T>& first,\n    const std::vector<T>& second\n) {\n    assert(\n\
    \        bitwise_or_convolution(first, second) ==\n        naive(first, second,\
    \ [](std::size_t i, std::size_t j) {\n            return i | j;\n        })\n\
    \    );\n    assert(\n        bitwise_and_convolution(first, second) ==\n    \
    \    naive(first, second, [](std::size_t i, std::size_t j) {\n            return\
    \ i & j;\n        })\n    );\n    assert(\n        bitwise_xor_convolution(first,\
    \ second) ==\n        naive(first, second, [](std::size_t i, std::size_t j) {\n\
    \            return i ^ j;\n        })\n    );\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 0x1234fedcba98765ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n       \
    \ std::size_t first_size = random() % 18;\n        std::size_t second_size = random()\
    \ % 18;\n        std::vector<long long> first(first_size);\n        std::vector<long\
    \ long> second(second_size);\n        for (long long& value : first) {\n     \
    \       value = static_cast<long long>(random() % 21) - 10;\n        }\n     \
    \   for (long long& value : second) {\n            value = static_cast<long long>(random()\
    \ % 21) - 10;\n        }\n        check_convolutions(first, second);\n    }\n\
    }\n\nvoid test_modint() {\n    using mint = m1une::math::modint998244353;\n  \
    \  std::vector<mint> first;\n    std::vector<mint> second;\n    for (int value\
    \ = 0; value < 13; ++value) {\n        first.emplace_back(value * value - 7);\n\
    \    }\n    for (int value = 0; value < 9; ++value) {\n        second.emplace_back(value\
    \ * 3 + 1);\n    }\n    check_convolutions(first, second);\n}\n\n}  // namespace\n\
    \nint main() {\n    test_transforms();\n    test_randomized();\n    test_modint();\n\
    \n    int n;\n    std::cin >> n;\n    int size = 1 << n;\n    using mint = m1une::math::modint998244353;\n\
    \    std::vector<mint> a(size), b(size);\n    for (int i = 0; i < size; i++) {\n\
    \        long long x;\n        std::cin >> x;\n        a[i] = x;\n    }\n    for\
    \ (int i = 0; i < size; i++) {\n        long long x;\n        std::cin >> x;\n\
    \        b[i] = x;\n    }\n    std::vector<mint> c = bitwise_xor_convolution(a,\
    \ b);\n    for (int i = 0; i < size; i++) {\n        if (i) std::cout << ' ';\n\
    \        std::cout << c[i].val();\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - math/bitwise_convolution.hpp
  - math/zeta_mobius_transform.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/bitwise_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/bitwise_convolution.test.cpp
layout: document
redirect_from:
- /verify/verify/math/bitwise_convolution.test.cpp
- /verify/verify/math/bitwise_convolution.test.cpp.html
title: verify/math/bitwise_convolution.test.cpp
---
