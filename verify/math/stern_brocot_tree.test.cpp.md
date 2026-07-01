---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/rational.hpp
    title: Rational Number
  - icon: ':question:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/math/stern_brocot_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/stern_brocot_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <limits>\n#include <utility>\n#include <vector>\n\n#line 1 \"math/rational.hpp\"\
    \n\n\n\n#line 5 \"math/rational.hpp\"\n#include <compare>\n#line 7 \"math/rational.hpp\"\
    \n#include <iostream>\n#line 9 \"math/rational.hpp\"\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral T = long\
    \ long>\nstruct Rational {\n    static_assert(sizeof(T) <= sizeof(long long));\n\
    \n   private:\n    using Wide = __int128_t;\n    using UnsignedWide = __uint128_t;\n\
    \n    T _numerator;\n    T _denominator;\n\n    static constexpr UnsignedWide\
    \ magnitude(Wide value) {\n        if (value < 0) {\n            return static_cast<UnsignedWide>(-(value\
    \ + 1)) + 1;\n        }\n        return static_cast<UnsignedWide>(value);\n  \
    \  }\n\n    static constexpr UnsignedWide gcd(UnsignedWide first, UnsignedWide\
    \ second) {\n        while (second != 0) {\n            UnsignedWide remainder\
    \ = first % second;\n            first = second;\n            second = remainder;\n\
    \        }\n        return first;\n    }\n\n    static constexpr T narrow(Wide\
    \ value) {\n        assert(Wide(std::numeric_limits<T>::min()) <= value);\n  \
    \      assert(value <= Wide(std::numeric_limits<T>::max()));\n        return static_cast<T>(value);\n\
    \    }\n\n    constexpr void assign_normalized(Wide numerator, Wide denominator)\
    \ {\n        assert(denominator != 0);\n        if (numerator == 0) {\n      \
    \      _numerator = 0;\n            _denominator = 1;\n            return;\n \
    \       }\n\n        UnsignedWide divisor = gcd(magnitude(numerator), magnitude(denominator));\n\
    \        numerator /= static_cast<Wide>(divisor);\n        denominator /= static_cast<Wide>(divisor);\n\
    \        if (denominator < 0) {\n            numerator = -numerator;\n       \
    \     denominator = -denominator;\n        }\n        _numerator = narrow(numerator);\n\
    \        _denominator = narrow(denominator);\n    }\n\n    static constexpr Rational\
    \ from_wide(Wide numerator, Wide denominator) {\n        Rational result;\n  \
    \      result.assign_normalized(numerator, denominator);\n        return result;\n\
    \    }\n\n   public:\n    constexpr Rational() : _numerator(0), _denominator(1)\
    \ {}\n\n    constexpr Rational(T integer) : _numerator(integer), _denominator(1)\
    \ {}\n\n    constexpr Rational(T numerator, T denominator) {\n        assign_normalized(Wide(numerator),\
    \ Wide(denominator));\n    }\n\n    constexpr T numerator() const {\n        return\
    \ _numerator;\n    }\n\n    constexpr T denominator() const {\n        return\
    \ _denominator;\n    }\n\n    constexpr bool is_integer() const {\n        return\
    \ _denominator == 1;\n    }\n\n    constexpr int sign() const {\n        return\
    \ (_numerator > 0) - (_numerator < 0);\n    }\n\n    constexpr Rational reciprocal()\
    \ const {\n        assert(_numerator != 0);\n        return from_wide(Wide(_denominator),\
    \ Wide(_numerator));\n    }\n\n    constexpr Rational abs() const {\n        return\
    \ _numerator < 0 ? -*this : *this;\n    }\n\n    constexpr long double to_long_double()\
    \ const {\n        return static_cast<long double>(_numerator) / static_cast<long\
    \ double>(_denominator);\n    }\n\n    explicit constexpr operator long double()\
    \ const {\n        return to_long_double();\n    }\n\n    constexpr T trunc()\
    \ const {\n        return _numerator / _denominator;\n    }\n\n    constexpr T\
    \ floor() const {\n        T quotient = _numerator / _denominator;\n        if\
    \ (_numerator < 0 && _numerator % _denominator != 0) --quotient;\n        return\
    \ quotient;\n    }\n\n    constexpr T ceil() const {\n        T quotient = _numerator\
    \ / _denominator;\n        if (0 < _numerator && _numerator % _denominator !=\
    \ 0) ++quotient;\n        return quotient;\n    }\n\n    constexpr Rational operator+()\
    \ const {\n        return *this;\n    }\n\n    constexpr Rational operator-()\
    \ const {\n        return from_wide(-Wide(_numerator), Wide(_denominator));\n\
    \    }\n\n    constexpr Rational& operator+=(const Rational& other) {\n      \
    \  UnsignedWide common =\n            gcd(static_cast<UnsignedWide>(_denominator),\
    \ static_cast<UnsignedWide>(other._denominator));\n        Wide left_scale = Wide(other._denominator)\
    \ / static_cast<Wide>(common);\n        Wide right_scale = Wide(_denominator)\
    \ / static_cast<Wide>(common);\n        assign_normalized(Wide(_numerator) * left_scale\
    \ + Wide(other._numerator) * right_scale,\n                          Wide(_denominator)\
    \ * left_scale);\n        return *this;\n    }\n\n    constexpr Rational& operator-=(const\
    \ Rational& other) {\n        return *this += -other;\n    }\n\n    constexpr\
    \ Rational& operator*=(const Rational& other) {\n        UnsignedWide first_gcd\
    \ = gcd(magnitude(Wide(_numerator)), static_cast<UnsignedWide>(other._denominator));\n\
    \        UnsignedWide second_gcd = gcd(magnitude(Wide(other._numerator)), static_cast<UnsignedWide>(_denominator));\n\
    \        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *\n\
    \                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),\n\
    \                          (Wide(_denominator) / static_cast<Wide>(second_gcd))\
    \ *\n                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator/=(const Rational&\
    \ other) {\n        return *this *= other.reciprocal();\n    }\n\n    friend constexpr\
    \ Rational operator+(Rational left, const Rational& right) {\n        return left\
    \ += right;\n    }\n\n    friend constexpr Rational operator-(Rational left, const\
    \ Rational& right) {\n        return left -= right;\n    }\n\n    friend constexpr\
    \ Rational operator*(Rational left, const Rational& right) {\n        return left\
    \ *= right;\n    }\n\n    friend constexpr Rational operator/(Rational left, const\
    \ Rational& right) {\n        return left /= right;\n    }\n\n    friend constexpr\
    \ bool operator==(const Rational& left, const Rational& right) {\n        return\
    \ left._numerator == right._numerator && left._denominator == right._denominator;\n\
    \    }\n\n    friend constexpr std::strong_ordering operator<=>(const Rational&\
    \ left, const Rational& right) {\n        Wide first = Wide(left._numerator) *\
    \ Wide(right._denominator);\n        Wide second = Wide(right._numerator) * Wide(left._denominator);\n\
    \        if (first < second) return std::strong_ordering::less;\n        if (second\
    \ < first) return std::strong_ordering::greater;\n        return std::strong_ordering::equal;\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& output, const Rational&\
    \ value) {\n        output << value._numerator;\n        if (value._denominator\
    \ != 1) {\n            output << '/' << value._denominator;\n        }\n     \
    \   return output;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ input, Rational& value) {\n        T numerator;\n        if (!(input >> numerator))\
    \ return input;\n        T denominator = 1;\n        if (input.peek() == '/')\
    \ {\n            input.get();\n            if (!(input >> denominator)) return\
    \ input;\n        }\n        value = Rational(numerator, denominator);\n     \
    \   return input;\n    }\n};\n\ntemplate <std::signed_integral T>\nconstexpr Rational<T>\
    \ abs(const Rational<T>& value) {\n    return value.abs();\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 12 \"math/stern_brocot_tree.hpp\"\n\n\
    namespace m1une {\nnamespace math {\n\nenum class SternBrocotDirection {\n   \
    \ Left,\n    Right,\n};\n\nstruct SternBrocotRun {\n    SternBrocotDirection direction;\n\
    \    uint64_t count;\n\n    friend bool operator==(const SternBrocotRun&, const\
    \ SternBrocotRun&) = default;\n};\n\nstruct SternBrocotPath {\n    std::vector<SternBrocotRun>\
    \ runs;\n\n    bool empty() const {\n        return runs.empty();\n    }\n\n \
    \   uint64_t depth() const {\n        uint64_t result = 0;\n        for (const\
    \ SternBrocotRun& run : runs) {\n            assert(run.count <= std::numeric_limits<uint64_t>::max()\
    \ - result);\n            result += run.count;\n        }\n        return result;\n\
    \    }\n\n    void push(SternBrocotDirection direction, uint64_t count = 1) {\n\
    \        if (count == 0) return;\n        if (!runs.empty() && runs.back().direction\
    \ == direction) {\n            assert(count <= std::numeric_limits<uint64_t>::max()\
    \ - runs.back().count);\n            runs.back().count += count;\n        } else\
    \ {\n            runs.push_back(SternBrocotRun{direction, count});\n        }\n\
    \    }\n\n    bool move_up(uint64_t count = 1) {\n        if (depth() < count)\
    \ return false;\n        while (count > 0) {\n            SternBrocotRun& run\
    \ = runs.back();\n            uint64_t removed = run.count < count ? run.count\
    \ : count;\n            run.count -= removed;\n            count -= removed;\n\
    \            if (run.count == 0) runs.pop_back();\n        }\n        return true;\n\
    \    }\n\n    SternBrocotPath ancestor(uint64_t count) const {\n        SternBrocotPath\
    \ result = *this;\n        [[maybe_unused]] bool valid = result.move_up(count);\n\
    \        assert(valid);\n        return result;\n    }\n\n    friend bool operator==(const\
    \ SternBrocotPath&, const SternBrocotPath&) = default;\n};\n\ntemplate <std::signed_integral\
    \ T = long long>\nstruct SternBrocotBounds {\n    std::pair<T, T> left;\n    std::pair<T,\
    \ T> right;\n};\n\ntemplate <std::signed_integral T>\nSternBrocotPath stern_brocot_path(T\
    \ numerator, T denominator) {\n    assert(0 < numerator);\n    assert(0 < denominator);\n\
    \    SternBrocotPath result;\n    while (numerator != denominator) {\n       \
    \ if (numerator < denominator) {\n            T count = (denominator - 1) / numerator;\n\
    \            result.push(SternBrocotDirection::Left, uint64_t(count));\n     \
    \       denominator -= count * numerator;\n        } else {\n            T count\
    \ = (numerator - 1) / denominator;\n            result.push(SternBrocotDirection::Right,\
    \ uint64_t(count));\n            numerator -= count * denominator;\n        }\n\
    \    }\n    assert(numerator == 1);\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T = long long>\nRational<T> stern_brocot_decode(const SternBrocotPath& path)\
    \ {\n    using Wide = __int128_t;\n    Wide left_numerator = 0;\n    Wide left_denominator\
    \ = 1;\n    Wide right_numerator = 1;\n    Wide right_denominator = 0;\n    Wide\
    \ numerator = 1;\n    Wide denominator = 1;\n    [[maybe_unused]] const Wide maximum\
    \ = std::numeric_limits<T>::max();\n    for (const SternBrocotRun& run : path.runs)\
    \ {\n        assert(run.count > 0);\n        assert(Wide(run.count) <= maximum);\n\
    \        Wide count = run.count;\n        if (run.direction == SternBrocotDirection::Left)\
    \ {\n            right_numerator = numerator + (count - 1) * left_numerator;\n\
    \            right_denominator = denominator + (count - 1) * left_denominator;\n\
    \            numerator += count * left_numerator;\n            denominator +=\
    \ count * left_denominator;\n        } else {\n            left_numerator = numerator\
    \ + (count - 1) * right_numerator;\n            left_denominator = denominator\
    \ + (count - 1) * right_denominator;\n            numerator += count * right_numerator;\n\
    \            denominator += count * right_denominator;\n        }\n        assert(numerator\
    \ <= maximum);\n        assert(denominator <= maximum);\n        assert(left_numerator\
    \ <= maximum);\n        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    return\
    \ Rational<T>(T(numerator), T(denominator));\n}\n\ntemplate <std::signed_integral\
    \ T>\nuint64_t stern_brocot_depth(T numerator, T denominator) {\n    return stern_brocot_path(numerator,\
    \ denominator).depth();\n}\n\ninline SternBrocotPath stern_brocot_lca_path(\n\
    \    const SternBrocotPath& first,\n    const SternBrocotPath& second\n) {\n \
    \   SternBrocotPath result;\n    int limit = int(first.runs.size() < second.runs.size()\
    \ ? first.runs.size() : second.runs.size());\n    for (int i = 0; i < limit; i++)\
    \ {\n        if (first.runs[i].direction != second.runs[i].direction) break;\n\
    \        uint64_t common =\n            first.runs[i].count < second.runs[i].count\n\
    \                ? first.runs[i].count\n                : second.runs[i].count;\n\
    \        result.push(first.runs[i].direction, common);\n        if (first.runs[i].count\
    \ != second.runs[i].count) break;\n    }\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T>\nRational<T> stern_brocot_lca(\n    T first_numerator,\n    T first_denominator,\n\
    \    T second_numerator,\n    T second_denominator\n) {\n    SternBrocotPath path\
    \ = stern_brocot_lca_path(\n        stern_brocot_path(first_numerator, first_denominator),\n\
    \        stern_brocot_path(second_numerator, second_denominator)\n    );\n   \
    \ return stern_brocot_decode<T>(path);\n}\n\ntemplate <std::signed_integral T>\n\
    Rational<T> stern_brocot_ancestor(T numerator, T denominator, uint64_t up) {\n\
    \    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n    [[maybe_unused]]\
    \ bool valid = path.move_up(up);\n    assert(valid);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_parent(T numerator,\
    \ T denominator) {\n    return stern_brocot_ancestor(numerator, denominator, 1);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_move(\n    T\
    \ numerator,\n    T denominator,\n    SternBrocotDirection direction,\n    uint64_t\
    \ count = 1\n) {\n    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n\
    \    path.push(direction, count);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T = long long>\nSternBrocotBounds<T> stern_brocot_bounds(const\
    \ SternBrocotPath& path) {\n    using Wide = __int128_t;\n    Wide left_numerator\
    \ = 0;\n    Wide left_denominator = 1;\n    Wide right_numerator = 1;\n    Wide\
    \ right_denominator = 0;\n    Wide numerator = 1;\n    Wide denominator = 1;\n\
    \    [[maybe_unused]] const Wide maximum = std::numeric_limits<T>::max();\n\n\
    \    for (const SternBrocotRun& run : path.runs) {\n        assert(run.count >\
    \ 0);\n        assert(Wide(run.count) <= maximum);\n        Wide count = run.count;\n\
    \        if (run.direction == SternBrocotDirection::Left) {\n            right_numerator\
    \ = numerator + (count - 1) * left_numerator;\n            right_denominator =\
    \ denominator + (count - 1) * left_denominator;\n            numerator += count\
    \ * left_numerator;\n            denominator += count * left_denominator;\n  \
    \      } else {\n            left_numerator = numerator + (count - 1) * right_numerator;\n\
    \            left_denominator = denominator + (count - 1) * right_denominator;\n\
    \            numerator += count * right_numerator;\n            denominator +=\
    \ count * right_denominator;\n        }\n        assert(numerator <= maximum);\n\
    \        assert(denominator <= maximum);\n        assert(left_numerator <= maximum);\n\
    \        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    SternBrocotBounds<T>\
    \ result;\n    result.left = {T(left_numerator), T(left_denominator)};\n    result.right\
    \ = {T(right_numerator), T(right_denominator)};\n    return result;\n}\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 4 \"verify/math/stern_brocot_tree.test.cpp\"\
    \n\n#line 8 \"verify/math/stern_brocot_tree.test.cpp\"\n#include <numeric>\n#line\
    \ 11 \"verify/math/stern_brocot_tree.test.cpp\"\n\nnamespace {\n\nusing Fraction\
    \ = m1une::math::Rational<long long>;\nusing Direction = m1une::math::SternBrocotDirection;\n\
    using Path = m1une::math::SternBrocotPath;\n\nstd::vector<Direction> expand(const\
    \ Path& path) {\n    std::vector<Direction> result;\n    for (const auto& run\
    \ : path.runs) {\n        for (uint64_t i = 0; i < run.count; i++) result.push_back(run.direction);\n\
    \    }\n    return result;\n}\n\nvoid test_features() {\n    Path root = m1une::math::stern_brocot_path(1LL,\
    \ 1LL);\n    assert(root.empty());\n    assert(root.depth() == 0);\n    assert(m1une::math::stern_brocot_decode<long\
    \ long>(root) == Fraction(1, 1));\n\n    Path path = m1une::math::stern_brocot_path(5LL,\
    \ 3LL);\n    assert(path.depth() == 3);\n    assert(path.runs.size() == 3);\n\
    \    m1une::math::SternBrocotRun right_once{Direction::Right, 1};\n    m1une::math::SternBrocotRun\
    \ left_once{Direction::Left, 1};\n    assert(path.runs[0] == right_once);\n  \
    \  assert(path.runs[1] == left_once);\n    assert(path.runs[2] == right_once);\n\
    \    assert(m1une::math::stern_brocot_decode<long long>(path) == Fraction(5, 3));\n\
    \    assert(m1une::math::stern_brocot_parent(5LL, 3LL) == Fraction(3, 2));\n \
    \   assert(m1une::math::stern_brocot_ancestor(5LL, 3LL, 2) == Fraction(2, 1));\n\
    \    assert(m1une::math::stern_brocot_ancestor(5LL, 3LL, 3) == Fraction(1, 1));\n\
    \n    assert(\n        m1une::math::stern_brocot_move(1LL, 1LL, Direction::Left,\
    \ 4)\n        == Fraction(1, 5)\n    );\n    assert(\n        m1une::math::stern_brocot_move(1LL,\
    \ 1LL, Direction::Right, 4)\n        == Fraction(5, 1)\n    );\n    assert(m1une::math::stern_brocot_lca(5LL,\
    \ 3LL, 7LL, 4LL) == Fraction(5, 3));\n    assert(m1une::math::stern_brocot_lca(2LL,\
    \ 5LL, 5LL, 2LL) == Fraction(1, 1));\n\n    auto bounds = m1une::math::stern_brocot_bounds<long\
    \ long>(path);\n    std::pair<long long, long long> expected_left(3, 2);\n   \
    \ std::pair<long long, long long> expected_right(2, 1);\n    assert(bounds.left\
    \ == expected_left);\n    assert(bounds.right == expected_right);\n}\n\nvoid test_exhaustive()\
    \ {\n    std::vector<Fraction> fractions;\n    std::vector<Path> paths;\n    for\
    \ (long long numerator = 1; numerator <= 100; numerator++) {\n        for (long\
    \ long denominator = 1; denominator <= 100; denominator++) {\n            if (std::gcd(numerator,\
    \ denominator) != 1) continue;\n            Path path = m1une::math::stern_brocot_path(numerator,\
    \ denominator);\n            Fraction decoded = m1une::math::stern_brocot_decode<long\
    \ long>(path);\n            assert(decoded == Fraction(numerator, denominator));\n\
    \            assert(path.depth() == m1une::math::stern_brocot_depth(numerator,\
    \ denominator));\n\n            auto bounds = m1une::math::stern_brocot_bounds<long\
    \ long>(path);\n            auto [left_numerator, left_denominator] = bounds.left;\n\
    \            auto [right_numerator, right_denominator] = bounds.right;\n     \
    \       assert(\n                __int128(numerator) * left_denominator\n    \
    \            - __int128(left_numerator) * denominator\n                == 1\n\
    \            );\n            assert(\n                __int128(right_numerator)\
    \ * denominator\n                - __int128(numerator) * right_denominator\n \
    \               == 1\n            );\n\n            auto left_child = m1une::math::stern_brocot_move(\n\
    \                numerator,\n                denominator,\n                Direction::Left\n\
    \            );\n            auto right_child = m1une::math::stern_brocot_move(\n\
    \                numerator,\n                denominator,\n                Direction::Right\n\
    \            );\n            assert(\n                left_child\n           \
    \     == Fraction(\n                    numerator + left_numerator,\n        \
    \            denominator + left_denominator\n                )\n            );\n\
    \            assert(\n                right_child\n                == Fraction(\n\
    \                    numerator + right_numerator,\n                    denominator\
    \ + right_denominator\n                )\n            );\n            assert(\n\
    \                m1une::math::stern_brocot_parent(\n                    left_child.numerator(),\n\
    \                    left_child.denominator()\n                )\n           \
    \     == Fraction(numerator, denominator)\n            );\n            assert(\n\
    \                m1une::math::stern_brocot_parent(\n                    right_child.numerator(),\n\
    \                    right_child.denominator()\n                )\n          \
    \      == Fraction(numerator, denominator)\n            );\n\n            fractions.emplace_back(numerator,\
    \ denominator);\n            paths.push_back(path);\n        }\n    }\n\n    for\
    \ (int first = 0; first < int(paths.size()); first += 17) {\n        for (int\
    \ second = 0; second < int(paths.size()); second += 23) {\n            std::vector<Direction>\
    \ first_expanded = expand(paths[first]);\n            std::vector<Direction> second_expanded\
    \ = expand(paths[second]);\n            int common = 0;\n            while (\n\
    \                common < int(first_expanded.size()) &&\n                common\
    \ < int(second_expanded.size()) &&\n                first_expanded[common] ==\
    \ second_expanded[common]\n            ) {\n                common++;\n      \
    \      }\n            Path expected;\n            for (int i = 0; i < common;\
    \ i++) expected.push(first_expanded[i]);\n            Path actual = m1une::math::stern_brocot_lca_path(paths[first],\
    \ paths[second]);\n            assert(actual == expected);\n            assert(\n\
    \                m1une::math::stern_brocot_lca(\n                    fractions[first].numerator(),\n\
    \                    fractions[first].denominator(),\n                    fractions[second].numerator(),\n\
    \                    fractions[second].denominator()\n                )\n    \
    \            == m1une::math::stern_brocot_decode<long long>(expected)\n      \
    \      );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_features();\n\
    \    test_exhaustive();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/stern_brocot_tree.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \nnamespace {\n\nusing Fraction = m1une::math::Rational<long long>;\nusing Direction\
    \ = m1une::math::SternBrocotDirection;\nusing Path = m1une::math::SternBrocotPath;\n\
    \nstd::vector<Direction> expand(const Path& path) {\n    std::vector<Direction>\
    \ result;\n    for (const auto& run : path.runs) {\n        for (uint64_t i =\
    \ 0; i < run.count; i++) result.push_back(run.direction);\n    }\n    return result;\n\
    }\n\nvoid test_features() {\n    Path root = m1une::math::stern_brocot_path(1LL,\
    \ 1LL);\n    assert(root.empty());\n    assert(root.depth() == 0);\n    assert(m1une::math::stern_brocot_decode<long\
    \ long>(root) == Fraction(1, 1));\n\n    Path path = m1une::math::stern_brocot_path(5LL,\
    \ 3LL);\n    assert(path.depth() == 3);\n    assert(path.runs.size() == 3);\n\
    \    m1une::math::SternBrocotRun right_once{Direction::Right, 1};\n    m1une::math::SternBrocotRun\
    \ left_once{Direction::Left, 1};\n    assert(path.runs[0] == right_once);\n  \
    \  assert(path.runs[1] == left_once);\n    assert(path.runs[2] == right_once);\n\
    \    assert(m1une::math::stern_brocot_decode<long long>(path) == Fraction(5, 3));\n\
    \    assert(m1une::math::stern_brocot_parent(5LL, 3LL) == Fraction(3, 2));\n \
    \   assert(m1une::math::stern_brocot_ancestor(5LL, 3LL, 2) == Fraction(2, 1));\n\
    \    assert(m1une::math::stern_brocot_ancestor(5LL, 3LL, 3) == Fraction(1, 1));\n\
    \n    assert(\n        m1une::math::stern_brocot_move(1LL, 1LL, Direction::Left,\
    \ 4)\n        == Fraction(1, 5)\n    );\n    assert(\n        m1une::math::stern_brocot_move(1LL,\
    \ 1LL, Direction::Right, 4)\n        == Fraction(5, 1)\n    );\n    assert(m1une::math::stern_brocot_lca(5LL,\
    \ 3LL, 7LL, 4LL) == Fraction(5, 3));\n    assert(m1une::math::stern_brocot_lca(2LL,\
    \ 5LL, 5LL, 2LL) == Fraction(1, 1));\n\n    auto bounds = m1une::math::stern_brocot_bounds<long\
    \ long>(path);\n    std::pair<long long, long long> expected_left(3, 2);\n   \
    \ std::pair<long long, long long> expected_right(2, 1);\n    assert(bounds.left\
    \ == expected_left);\n    assert(bounds.right == expected_right);\n}\n\nvoid test_exhaustive()\
    \ {\n    std::vector<Fraction> fractions;\n    std::vector<Path> paths;\n    for\
    \ (long long numerator = 1; numerator <= 100; numerator++) {\n        for (long\
    \ long denominator = 1; denominator <= 100; denominator++) {\n            if (std::gcd(numerator,\
    \ denominator) != 1) continue;\n            Path path = m1une::math::stern_brocot_path(numerator,\
    \ denominator);\n            Fraction decoded = m1une::math::stern_brocot_decode<long\
    \ long>(path);\n            assert(decoded == Fraction(numerator, denominator));\n\
    \            assert(path.depth() == m1une::math::stern_brocot_depth(numerator,\
    \ denominator));\n\n            auto bounds = m1une::math::stern_brocot_bounds<long\
    \ long>(path);\n            auto [left_numerator, left_denominator] = bounds.left;\n\
    \            auto [right_numerator, right_denominator] = bounds.right;\n     \
    \       assert(\n                __int128(numerator) * left_denominator\n    \
    \            - __int128(left_numerator) * denominator\n                == 1\n\
    \            );\n            assert(\n                __int128(right_numerator)\
    \ * denominator\n                - __int128(numerator) * right_denominator\n \
    \               == 1\n            );\n\n            auto left_child = m1une::math::stern_brocot_move(\n\
    \                numerator,\n                denominator,\n                Direction::Left\n\
    \            );\n            auto right_child = m1une::math::stern_brocot_move(\n\
    \                numerator,\n                denominator,\n                Direction::Right\n\
    \            );\n            assert(\n                left_child\n           \
    \     == Fraction(\n                    numerator + left_numerator,\n        \
    \            denominator + left_denominator\n                )\n            );\n\
    \            assert(\n                right_child\n                == Fraction(\n\
    \                    numerator + right_numerator,\n                    denominator\
    \ + right_denominator\n                )\n            );\n            assert(\n\
    \                m1une::math::stern_brocot_parent(\n                    left_child.numerator(),\n\
    \                    left_child.denominator()\n                )\n           \
    \     == Fraction(numerator, denominator)\n            );\n            assert(\n\
    \                m1une::math::stern_brocot_parent(\n                    right_child.numerator(),\n\
    \                    right_child.denominator()\n                )\n          \
    \      == Fraction(numerator, denominator)\n            );\n\n            fractions.emplace_back(numerator,\
    \ denominator);\n            paths.push_back(path);\n        }\n    }\n\n    for\
    \ (int first = 0; first < int(paths.size()); first += 17) {\n        for (int\
    \ second = 0; second < int(paths.size()); second += 23) {\n            std::vector<Direction>\
    \ first_expanded = expand(paths[first]);\n            std::vector<Direction> second_expanded\
    \ = expand(paths[second]);\n            int common = 0;\n            while (\n\
    \                common < int(first_expanded.size()) &&\n                common\
    \ < int(second_expanded.size()) &&\n                first_expanded[common] ==\
    \ second_expanded[common]\n            ) {\n                common++;\n      \
    \      }\n            Path expected;\n            for (int i = 0; i < common;\
    \ i++) expected.push(first_expanded[i]);\n            Path actual = m1une::math::stern_brocot_lca_path(paths[first],\
    \ paths[second]);\n            assert(actual == expected);\n            assert(\n\
    \                m1une::math::stern_brocot_lca(\n                    fractions[first].numerator(),\n\
    \                    fractions[first].denominator(),\n                    fractions[second].numerator(),\n\
    \                    fractions[second].denominator()\n                )\n    \
    \            == m1une::math::stern_brocot_decode<long long>(expected)\n      \
    \      );\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_features();\n\
    \    test_exhaustive();\n\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b << '\\n';\n}\n"
  dependsOn:
  - math/stern_brocot_tree.hpp
  - math/rational.hpp
  isVerificationFile: true
  path: verify/math/stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-24 14:07:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/math/stern_brocot_tree.test.cpp
- /verify/verify/math/stern_brocot_tree.test.cpp.html
title: verify/math/stern_brocot_tree.test.cpp
---
