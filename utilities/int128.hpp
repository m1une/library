#ifndef M1UNE_INT128_HPP
#define M1UNE_INT128_HPP 1

#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace m1une {
namespace utilities {

using i128 = __int128_t;
using u128 = __uint128_t;

inline std::string to_string(u128 x) {
    if (x == 0) {
        return "0";
    }
    std::string s;
    while (x > 0) {
        s.push_back(static_cast<char>('0' + x % 10));
        x /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

inline std::string to_string(i128 x) {
    if (x < 0) {
        u128 magnitude = static_cast<u128>(-(x + 1)) + 1;
        return "-" + to_string(magnitude);
    }
    return to_string(static_cast<u128>(x));
}

inline u128 parse_uint128(const std::string& s) {
    if (s.empty()) {
        throw std::invalid_argument("empty string");
    }
    u128 value = 0;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("invalid unsigned __int128 literal");
        }
        value = value * 10 + static_cast<unsigned>(c - '0');
    }
    return value;
}

inline i128 parse_int128(const std::string& s) {
    if (s.empty()) {
        throw std::invalid_argument("empty string");
    }
    bool negative = s[0] == '-';
    std::size_t pos = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    if (pos == s.size()) {
        throw std::invalid_argument("invalid __int128 literal");
    }

    i128 value = 0;
    for (; pos < s.size(); ++pos) {
        char c = s[pos];
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("invalid __int128 literal");
        }
        int digit = c - '0';
        value = value * 10 + (negative ? -digit : digit);
    }
    return value;
}

}  // namespace utilities
}  // namespace m1une

inline std::ostream& operator<<(std::ostream& os, __uint128_t x) {
    return os << m1une::utilities::to_string(x);
}

inline std::ostream& operator<<(std::ostream& os, __int128_t x) {
    return os << m1une::utilities::to_string(x);
}

inline std::istream& operator>>(std::istream& is, __uint128_t& x) {
    std::string s;
    is >> s;
    if (is) {
        x = m1une::utilities::parse_uint128(s);
    }
    return is;
}

inline std::istream& operator>>(std::istream& is, __int128_t& x) {
    std::string s;
    is >> s;
    if (is) {
        x = m1une::utilities::parse_int128(s);
    }
    return is;
}

#endif  // M1UNE_INT128_HPP
