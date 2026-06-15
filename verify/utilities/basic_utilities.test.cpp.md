---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/int128.hpp
    title: Int128
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
  - icon: ':heavy_check_mark:'
    path: utilities/timer.hpp
    title: Timer
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
  bundledCode: "#line 1 \"verify/utilities/basic_utilities.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n\n#line 1 \"utilities/int128.hpp\"\n\n\n\n#line 10 \"utilities/int128.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\nusing i128 = __int128_t;\nusing\
    \ u128 = __uint128_t;\n\ninline std::string to_string(u128 x) {\n    if (x ==\
    \ 0) {\n        return \"0\";\n    }\n    std::string s;\n    while (x > 0) {\n\
    \        s.push_back(static_cast<char>('0' + x % 10));\n        x /= 10;\n   \
    \ }\n    std::reverse(s.begin(), s.end());\n    return s;\n}\n\ninline std::string\
    \ to_string(i128 x) {\n    if (x < 0) {\n        u128 magnitude = static_cast<u128>(-(x\
    \ + 1)) + 1;\n        return \"-\" + to_string(magnitude);\n    }\n    return\
    \ to_string(static_cast<u128>(x));\n}\n\ninline u128 parse_uint128(const std::string&\
    \ s) {\n    if (s.empty()) {\n        throw std::invalid_argument(\"empty string\"\
    );\n    }\n    u128 value = 0;\n    for (char c : s) {\n        if (!std::isdigit(static_cast<unsigned\
    \ char>(c))) {\n            throw std::invalid_argument(\"invalid unsigned __int128\
    \ literal\");\n        }\n        value = value * 10 + static_cast<unsigned>(c\
    \ - '0');\n    }\n    return value;\n}\n\ninline i128 parse_int128(const std::string&\
    \ s) {\n    if (s.empty()) {\n        throw std::invalid_argument(\"empty string\"\
    );\n    }\n    bool negative = s[0] == '-';\n    std::size_t pos = (s[0] == '-'\
    \ || s[0] == '+') ? 1 : 0;\n    if (pos == s.size()) {\n        throw std::invalid_argument(\"\
    invalid __int128 literal\");\n    }\n\n    i128 value = 0;\n    for (; pos < s.size();\
    \ ++pos) {\n        char c = s[pos];\n        if (!std::isdigit(static_cast<unsigned\
    \ char>(c))) {\n            throw std::invalid_argument(\"invalid __int128 literal\"\
    );\n        }\n        int digit = c - '0';\n        value = value * 10 + (negative\
    \ ? -digit : digit);\n    }\n    return value;\n}\n\n}  // namespace utilities\n\
    }  // namespace m1une\n\ninline std::ostream& operator<<(std::ostream& os, __uint128_t\
    \ x) {\n    return os << m1une::utilities::to_string(x);\n}\n\ninline std::ostream&\
    \ operator<<(std::ostream& os, __int128_t x) {\n    return os << m1une::utilities::to_string(x);\n\
    }\n\ninline std::istream& operator>>(std::istream& is, __uint128_t& x) {\n   \
    \ std::string s;\n    is >> s;\n    if (is) {\n        x = m1une::utilities::parse_uint128(s);\n\
    \    }\n    return is;\n}\n\ninline std::istream& operator>>(std::istream& is,\
    \ __int128_t& x) {\n    std::string s;\n    is >> s;\n    if (is) {\n        x\
    \ = m1une::utilities::parse_int128(s);\n    }\n    return is;\n}\n\n\n#line 1\
    \ \"utilities/random.hpp\"\n\n\n\n#line 8 \"utilities/random.hpp\"\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\nstruct Random {\n   private:\n    std::mt19937_64\
    \ _engine;\n\n    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
    \ long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    }\n\n   public:\n    Random() : _engine(chrono_seed()) {}\n    explicit Random(unsigned\
    \ long long seed) : _engine(seed) {}\n\n    void seed(unsigned long long value)\
    \ {\n        _engine.seed(value);\n    }\n\n    std::mt19937_64& engine() {\n\
    \        return _engine;\n    }\n\n    unsigned long long operator()() {\n   \
    \     return _engine();\n    }\n\n    long long uniform(long long l, long long\
    \ r) {\n        return std::uniform_int_distribution<long long>(l, r)(_engine);\n\
    \    }\n\n    unsigned long long uniform_unsigned(unsigned long long l, unsigned\
    \ long long r) {\n        return std::uniform_int_distribution<unsigned long long>(l,\
    \ r)(_engine);\n    }\n\n    double real(double l = 0.0, double r = 1.0) {\n \
    \       return std::uniform_real_distribution<double>(l, r)(_engine);\n    }\n\
    \n    template <typename T>\n    void shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(),\
    \ v.end(), _engine);\n    }\n\n    template <typename Iterator>\n    void shuffle(Iterator\
    \ first, Iterator last) {\n        std::shuffle(first, last, _engine);\n    }\n\
    \n    template <typename T>\n    const T& choice(const std::vector<T>& v) {\n\
    \        return v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n\
    };\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/timer.hpp\"\
    \n\n\n\n#line 5 \"utilities/timer.hpp\"\n\nnamespace m1une {\nnamespace utilities\
    \ {\n\nstruct Timer {\n   private:\n    using clock = std::chrono::steady_clock;\n\
    \n    clock::time_point _start;\n    double _limit;\n\n   public:\n    explicit\
    \ Timer(double limit_seconds = 0.0) : _start(clock::now()), _limit(limit_seconds)\
    \ {}\n\n    void reset() {\n        _start = clock::now();\n    }\n\n    void\
    \ set_limit(double limit_seconds) {\n        _limit = limit_seconds;\n    }\n\n\
    \    double elapsed() const {\n        return std::chrono::duration<double>(clock::now()\
    \ - _start).count();\n    }\n\n    long long elapsed_ms() const {\n        return\
    \ std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - _start).count();\n\
    \    }\n\n    bool expired() const {\n        return elapsed() >= _limit;\n  \
    \  }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/utilities/basic_utilities.test.cpp\"\
    \n\nvoid test_int128() {\n    using m1une::utilities::i128;\n    using m1une::utilities::parse_int128;\n\
    \    using m1une::utilities::parse_uint128;\n    using m1une::utilities::to_string;\n\
    \    using m1une::utilities::u128;\n\n    i128 x = parse_int128(\"-170141183460469231731687303715884105\"\
    );\n    assert(to_string(x) == \"-170141183460469231731687303715884105\");\n\n\
    \    u128 y = parse_uint128(\"340282366920938463463374607431768211\");\n    assert(to_string(y)\
    \ == \"340282366920938463463374607431768211\");\n\n    stringstream ss;\n    ss\
    \ << x << \" \" << y;\n    assert(ss.str() == \"-170141183460469231731687303715884105\
    \ 340282366920938463463374607431768211\");\n\n    i128 read_x;\n    u128 read_y;\n\
    \    ss >> read_x >> read_y;\n    assert(read_x == x);\n    assert(read_y == y);\n\
    }\n\nvoid test_random() {\n    m1une::utilities::Random rng1(42), rng2(42);\n\
    \    for (int i = 0; i < 10; ++i) {\n        assert(rng1() == rng2());\n    }\n\
    \n    for (int i = 0; i < 100; ++i) {\n        long long x = rng1.uniform(-5,\
    \ 5);\n        assert(-5 <= x && x <= 5);\n        double y = rng1.real(-1.0,\
    \ 2.0);\n        assert(-1.0 <= y && y < 2.0);\n    }\n\n    vector<int> v = {1,\
    \ 2, 3, 4, 5};\n    rng1.shuffle(v);\n    sort(v.begin(), v.end());\n    assert((v\
    \ == vector<int>{1, 2, 3, 4, 5}));\n    int picked = rng1.choice(v);\n    assert(1\
    \ <= picked && picked <= 5);\n}\n\nvoid test_timer() {\n    m1une::utilities::Timer\
    \ timer(0.0);\n    assert(timer.elapsed() >= 0.0);\n    assert(timer.elapsed_ms()\
    \ >= 0);\n    assert(timer.expired());\n    timer.set_limit(1000000.0);\n    timer.reset();\n\
    \    assert(!timer.expired());\n}\n\nint main() {\n    test_int128();\n    test_random();\n\
    \    test_timer();\n\n    long long a, b;\n    cin >> a >> b;\n    cout << a +\
    \ b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#include \"utilities/int128.hpp\"\n#include \"utilities/random.hpp\"\
    \n#include \"utilities/timer.hpp\"\n\nvoid test_int128() {\n    using m1une::utilities::i128;\n\
    \    using m1une::utilities::parse_int128;\n    using m1une::utilities::parse_uint128;\n\
    \    using m1une::utilities::to_string;\n    using m1une::utilities::u128;\n\n\
    \    i128 x = parse_int128(\"-170141183460469231731687303715884105\");\n    assert(to_string(x)\
    \ == \"-170141183460469231731687303715884105\");\n\n    u128 y = parse_uint128(\"\
    340282366920938463463374607431768211\");\n    assert(to_string(y) == \"340282366920938463463374607431768211\"\
    );\n\n    stringstream ss;\n    ss << x << \" \" << y;\n    assert(ss.str() ==\
    \ \"-170141183460469231731687303715884105 340282366920938463463374607431768211\"\
    );\n\n    i128 read_x;\n    u128 read_y;\n    ss >> read_x >> read_y;\n    assert(read_x\
    \ == x);\n    assert(read_y == y);\n}\n\nvoid test_random() {\n    m1une::utilities::Random\
    \ rng1(42), rng2(42);\n    for (int i = 0; i < 10; ++i) {\n        assert(rng1()\
    \ == rng2());\n    }\n\n    for (int i = 0; i < 100; ++i) {\n        long long\
    \ x = rng1.uniform(-5, 5);\n        assert(-5 <= x && x <= 5);\n        double\
    \ y = rng1.real(-1.0, 2.0);\n        assert(-1.0 <= y && y < 2.0);\n    }\n\n\
    \    vector<int> v = {1, 2, 3, 4, 5};\n    rng1.shuffle(v);\n    sort(v.begin(),\
    \ v.end());\n    assert((v == vector<int>{1, 2, 3, 4, 5}));\n    int picked =\
    \ rng1.choice(v);\n    assert(1 <= picked && picked <= 5);\n}\n\nvoid test_timer()\
    \ {\n    m1une::utilities::Timer timer(0.0);\n    assert(timer.elapsed() >= 0.0);\n\
    \    assert(timer.elapsed_ms() >= 0);\n    assert(timer.expired());\n    timer.set_limit(1000000.0);\n\
    \    timer.reset();\n    assert(!timer.expired());\n}\n\nint main() {\n    test_int128();\n\
    \    test_random();\n    test_timer();\n\n    long long a, b;\n    cin >> a >>\
    \ b;\n    cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/int128.hpp
  - utilities/random.hpp
  - utilities/timer.hpp
  isVerificationFile: true
  path: verify/utilities/basic_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-06-15 23:35:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/basic_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/basic_utilities.test.cpp
- /verify/verify/utilities/basic_utilities.test.cpp.html
title: verify/utilities/basic_utilities.test.cpp
---
