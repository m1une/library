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
    PROBLEM: https://judge.yosupo.jp/problem/stern_brocot_tree
    links:
    - https://judge.yosupo.jp/problem/stern_brocot_tree
  bundledCode: "#line 1 \"verify/math/yosupo_stern_brocot_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#line 1 \"math/stern_brocot_tree.hpp\"\n\n\n\n#line 5\
    \ \"math/stern_brocot_tree.hpp\"\n#include <concepts>\n#line 10 \"math/stern_brocot_tree.hpp\"\
    \n\n#line 1 \"math/rational.hpp\"\n\n\n\n#line 5 \"math/rational.hpp\"\n#include\
    \ <compare>\n#line 9 \"math/rational.hpp\"\n#include <type_traits>\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <std::signed_integral T = long long>\n\
    struct Rational {\n    static_assert(sizeof(T) <= sizeof(long long));\n\n   private:\n\
    \    using Wide = __int128_t;\n    using UnsignedWide = __uint128_t;\n\n    T\
    \ _numerator;\n    T _denominator;\n\n    static constexpr UnsignedWide magnitude(Wide\
    \ value) {\n        if (value < 0) {\n            return static_cast<UnsignedWide>(-(value\
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
    \ namespace math\n}  // namespace m1une\n\n\n#line 7 \"verify/math/yosupo_stern_brocot_tree.test.cpp\"\
    \nusing ll = long long;\n\nint main() {\n    ios::sync_with_stdio(false);\n  \
    \  cin.tie(nullptr);\n    ll T;\n    cin >> T;\n    while (T--) {\n        string\
    \ s;\n        cin >> s;\n        if (s == \"ENCODE_PATH\") {\n            ll a,\
    \ b;\n            cin >> a >> b;\n            auto path = m1une::math::stern_brocot_path(a,\
    \ b);\n            auto& runs = path.runs;\n            cout << runs.size();\n\
    \            for (auto& dir : runs) {\n                if (dir.direction == m1une::math::SternBrocotDirection::Left)\
    \ {\n                    cout << \" L \" << dir.count;\n                } else\
    \ {\n                    cout << \" R \" << dir.count;\n                }\n  \
    \          }\n            cout << '\\n';\n        } else if (s == \"DECODE_PATH\"\
    ) {\n            m1une::math::SternBrocotPath path;\n            ll k;\n     \
    \       cin >> k;\n            while (k--) {\n                char c;\n      \
    \          cin >> c;\n                ll n;\n                cin >> n;\n     \
    \           if (c == 'L') {\n                    path.push(m1une::math::SternBrocotDirection::Left,\
    \ n);\n                } else if (c == 'R') {\n                    path.push(m1une::math::SternBrocotDirection::Right,\
    \ n);\n                } else {\n                    exit(1);\n              \
    \  }\n            }\n            auto r = m1une::math::stern_brocot_decode(path);\n\
    \            cout << r.numerator() << ' ' << r.denominator() << '\\n';\n     \
    \   } else if (s == \"LCA\") {\n            ll a, b, c, d;\n            cin >>\
    \ a >> b >> c >> d;\n            auto r = m1une::math::stern_brocot_lca(a, b,\
    \ c, d);\n            cout << r.numerator() << ' ' << r.denominator() << '\\n';\n\
    \        } else if (s == \"ANCESTOR\") {\n            ll k, a, b;\n          \
    \  cin >> k >> a >> b;\n            ll d = m1une::math::stern_brocot_depth(a,\
    \ b);\n            if (d < k) {\n                cout << \"-1\\n\";\n        \
    \    } else {\n                auto r = m1une::math::stern_brocot_ancestor(a,\
    \ b, d - k);\n                cout << r.numerator() << ' ' << r.denominator()\
    \ << '\\n';\n            }\n        } else if (s == \"RANGE\") {\n           \
    \ ll a, b;\n            cin >> a >> b;\n            auto path = m1une::math::stern_brocot_path(a,\
    \ b);\n            auto bound = m1une::math::stern_brocot_bounds(path);\n    \
    \        cout << bound.left.first << ' ' << bound.left.second << ' ' << bound.right.first\
    \ << ' ' << bound.right.second\n                 << '\\n';\n        } else {\n\
    \            exit(1);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n\
    #include <bits/stdc++.h>\nusing namespace std;\n\n#include \"math/stern_brocot_tree.hpp\"\
    \nusing ll = long long;\n\nint main() {\n    ios::sync_with_stdio(false);\n  \
    \  cin.tie(nullptr);\n    ll T;\n    cin >> T;\n    while (T--) {\n        string\
    \ s;\n        cin >> s;\n        if (s == \"ENCODE_PATH\") {\n            ll a,\
    \ b;\n            cin >> a >> b;\n            auto path = m1une::math::stern_brocot_path(a,\
    \ b);\n            auto& runs = path.runs;\n            cout << runs.size();\n\
    \            for (auto& dir : runs) {\n                if (dir.direction == m1une::math::SternBrocotDirection::Left)\
    \ {\n                    cout << \" L \" << dir.count;\n                } else\
    \ {\n                    cout << \" R \" << dir.count;\n                }\n  \
    \          }\n            cout << '\\n';\n        } else if (s == \"DECODE_PATH\"\
    ) {\n            m1une::math::SternBrocotPath path;\n            ll k;\n     \
    \       cin >> k;\n            while (k--) {\n                char c;\n      \
    \          cin >> c;\n                ll n;\n                cin >> n;\n     \
    \           if (c == 'L') {\n                    path.push(m1une::math::SternBrocotDirection::Left,\
    \ n);\n                } else if (c == 'R') {\n                    path.push(m1une::math::SternBrocotDirection::Right,\
    \ n);\n                } else {\n                    exit(1);\n              \
    \  }\n            }\n            auto r = m1une::math::stern_brocot_decode(path);\n\
    \            cout << r.numerator() << ' ' << r.denominator() << '\\n';\n     \
    \   } else if (s == \"LCA\") {\n            ll a, b, c, d;\n            cin >>\
    \ a >> b >> c >> d;\n            auto r = m1une::math::stern_brocot_lca(a, b,\
    \ c, d);\n            cout << r.numerator() << ' ' << r.denominator() << '\\n';\n\
    \        } else if (s == \"ANCESTOR\") {\n            ll k, a, b;\n          \
    \  cin >> k >> a >> b;\n            ll d = m1une::math::stern_brocot_depth(a,\
    \ b);\n            if (d < k) {\n                cout << \"-1\\n\";\n        \
    \    } else {\n                auto r = m1une::math::stern_brocot_ancestor(a,\
    \ b, d - k);\n                cout << r.numerator() << ' ' << r.denominator()\
    \ << '\\n';\n            }\n        } else if (s == \"RANGE\") {\n           \
    \ ll a, b;\n            cin >> a >> b;\n            auto path = m1une::math::stern_brocot_path(a,\
    \ b);\n            auto bound = m1une::math::stern_brocot_bounds(path);\n    \
    \        cout << bound.left.first << ' ' << bound.left.second << ' ' << bound.right.first\
    \ << ' ' << bound.right.second\n                 << '\\n';\n        } else {\n\
    \            exit(1);\n        }\n    }\n}\n"
  dependsOn:
  - math/stern_brocot_tree.hpp
  - math/rational.hpp
  isVerificationFile: true
  path: verify/math/yosupo_stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-24 14:23:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/yosupo_stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/math/yosupo_stern_brocot_tree.test.cpp
- /verify/verify/math/yosupo_stern_brocot_tree.test.cpp.html
title: verify/math/yosupo_stern_brocot_tree.test.cpp
---
