---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/rational.hpp
    title: Rational Number
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/stern_brocot_tree.test.cpp
    title: verify/math/stern_brocot_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/yosupo_stern_brocot_tree.test.cpp
    title: verify/math/yosupo_stern_brocot_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/stern_brocot_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"math/rational.hpp\"\n\n\n\n#line 5 \"math/rational.hpp\"\
    \n#include <compare>\n#line 7 \"math/rational.hpp\"\n#include <iostream>\n#line\
    \ 9 \"math/rational.hpp\"\n#include <type_traits>\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <std::signed_integral T = long long>\nstruct Rational {\n\
    \    static_assert(sizeof(T) <= sizeof(long long));\n\n   private:\n    using\
    \ Wide = __int128_t;\n    using UnsignedWide = __uint128_t;\n\n    T _numerator;\n\
    \    T _denominator;\n\n    static constexpr UnsignedWide magnitude(Wide value)\
    \ {\n        if (value < 0) {\n            return static_cast<UnsignedWide>(-(value\
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
    \ namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_STERN_BROCOT_TREE_HPP\n#define M1UNE_MATH_STERN_BROCOT_TREE_HPP\
    \ 1\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <limits>\n\
    #include <utility>\n#include <vector>\n\n#include \"rational.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\nenum class SternBrocotDirection {\n    Left,\n\
    \    Right,\n};\n\nstruct SternBrocotRun {\n    SternBrocotDirection direction;\n\
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
    \ namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_STERN_BROCOT_TREE_HPP\n"
  dependsOn:
  - math/rational.hpp
  isVerificationFile: false
  path: math/stern_brocot_tree.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-24 14:07:51+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/yosupo_stern_brocot_tree.test.cpp
  - verify/math/stern_brocot_tree.test.cpp
documentation_of: math/stern_brocot_tree.hpp
layout: document
title: Stern-Brocot Tree
---

## Overview

The Stern-Brocot tree contains every positive reduced rational exactly once.
It is useful when rational numbers must be handled by their position in the
tree instead of by floating point values: comparing continued-fraction-like
paths, finding the lowest common ancestor of two fractions, walking to a
parent/child, or representing a whole interval of fractions by one node.

The root is `1/1`. Each node represents the mediant of two boundary fractions
`L` and `R`; the left child replaces the right boundary by the current fraction,
and the right child replaces the left boundary by the current fraction.

This library stores a path from the root in run-length form, such as `L^3 R^2`,
rather than one direction per edge. Encoding a fraction is essentially the
Euclidean algorithm, so very deep paths such as `1/10^18` are represented by one
run instead of `10^18 - 1` individual moves.

All fraction-returning operations use `Rational<T>`.

## Model

The root path is empty and decodes to `1/1`.

For a path, `stern_brocot_bounds(path)` returns the open interval containing
exactly the fractions in the subtree rooted at that path. Boundaries are stored
as `(numerator, denominator)` pairs because the right boundary of the whole
tree is positive infinity, represented by `1/0`.

For example, the path to `5/3` is `R L R`:

```text
1/1 --R--> 2/1 --L--> 3/2 --R--> 5/3
```

## Path Types

`SternBrocotDirection` has values `Left` and `Right`.

`SternBrocotRun` stores a direction and positive repetition count.

`SternBrocotPath` exposes:

| Method | Description |
| --- | --- |
| `bool empty() const` | Whether the path denotes the root. |
| `uint64_t depth() const` | Expanded edge count. |
| `void push(direction, count)` | Appends moves and merges equal adjacent directions. |
| `bool move_up(count)` | Removes edges; returns false if the ancestor is above the root. |
| `SternBrocotPath ancestor(count) const` | Returns an ancestor path; requires sufficient depth. |

`push` accepts `count = 0` and does nothing. A valid stored run has positive
count; decoding or bound construction asserts this condition.

## Functions

All functions are in namespace `m1une::math`. Template parameter `T` must be a
signed integer type supported by `Rational<T>`, such as `int` or `long long`.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class T>`<br>`SternBrocotPath stern_brocot_path(T p, T q)` | Encodes the positive reduced fraction `p/q`. | `O(log max(p,q))` runs |
| `template<class T = long long>`<br>`Rational<T> stern_brocot_decode(const SternBrocotPath& path)` | Decodes a path. | `O(number of runs)` |
| `template<class T>`<br>`uint64_t stern_brocot_depth(T p, T q)` | Returns the expanded tree depth. | `O(log max(p,q))` |
| `SternBrocotPath stern_brocot_lca_path(const SternBrocotPath& a, const SternBrocotPath& b)` | Returns the compressed common path prefix. | `O(number of runs)` |
| `template<class T>`<br>`Rational<T> stern_brocot_lca(T a, T b, T c, T d)` | Returns the LCA of `a/b` and `c/d`. | `O(log max values)` |
| `template<class T>`<br>`Rational<T> stern_brocot_ancestor(T p, T q, uint64_t up)` | Returns the ancestor `up` edges above `p/q`. | `O(number of runs)` |
| `template<class T>`<br>`Rational<T> stern_brocot_parent(T p, T q)` | Returns the parent. | `O(log max(p,q))` |
| `template<class T>`<br>`Rational<T> stern_brocot_move(T p, T q, SternBrocotDirection direction, uint64_t count = 1)` | Descends repeatedly. | `O(log max(p,q))` |
| `template<class T = long long>`<br>`SternBrocotBounds<T> stern_brocot_bounds(const SternBrocotPath& path)` | Returns the open interval boundaries of the path subtree. | `O(number of runs)` |

Here `O(log max(p,q))` means the number of Euclidean divisions, not the expanded
tree depth. For example, `stern_brocot_path(1, 1000000000000000000)` creates one
run.

`SternBrocotBounds<T>` stores:

| Member | Type | Meaning |
| --- | --- | --- |
| `left` | `std::pair<T, T>` | Left boundary fraction `(numerator, denominator)`. |
| `right` | `std::pair<T, T>` | Right boundary fraction `(numerator, denominator)`. |

## Contracts

Inputs to `stern_brocot_path` and functions that encode a fraction must satisfy:

- `p > 0`
- `q > 0`
- `gcd(p, q) = 1`

These conditions are asserted in debug builds.

Additional preconditions:

- Decoded numerators, denominators, and interval boundaries must fit in `T`.
- `stern_brocot_ancestor(p, q, up)` requires `up <= stern_brocot_depth(p, q)`.
- `stern_brocot_parent(p, q)` requires `p/q != 1/1`.
- A manually created `SternBrocotPath` must contain only positive-count runs.

These are CP-style direct-return functions. Invalid calls are programmer errors
and are checked with assertions where practical.

## Example

```cpp
#include "math/stern_brocot_tree.hpp"
#include <iostream>

int main() {
    auto path = m1une::math::stern_brocot_path(5LL, 3LL);
    std::cout << path.depth() << '\n';  // 3

    auto same = m1une::math::stern_brocot_decode<long long>(path);
    std::cout << same << '\n';  // 5/3

    auto parent = m1une::math::stern_brocot_parent(5LL, 3LL);
    std::cout << parent << '\n';  // 3/2

    auto lca = m1une::math::stern_brocot_lca(5LL, 3LL, 7LL, 4LL);
    std::cout << lca << '\n';  // 5/3

    auto bounds = m1une::math::stern_brocot_bounds<long long>(path);
    std::cout << bounds.left.first << '/' << bounds.left.second << '\n';    // 3/2
    std::cout << bounds.right.first << '/' << bounds.right.second << '\n';  // 2/1
}
```

## Notes

- The order of paths is not lexicographic order of fractions. Use this library
  when tree structure matters; use `Rational<T>` comparisons when numeric order
  matters.
- The subtree interval is open: the boundary fractions themselves are not inside
  the subtree.
- Run-length paths make ancestor and LCA operations fast even for fractions with
  enormous expanded depth.
