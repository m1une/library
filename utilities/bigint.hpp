#ifndef M1UNE_UTILITIES_BIGINT_HPP
#define M1UNE_UTILITIES_BIGINT_HPP 1

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace m1une {
namespace utilities {

struct BigInt {
    static constexpr int BASE = 1000000000;
    static constexpr int BASE_DIGITS = 9;

    std::vector<int> a;
    int sign;

    BigInt() : sign(1) {}

    BigInt(long long v) {
        *this = v;
    }

    BigInt(const std::string& s) {
        read(s);
    }

    BigInt& operator=(long long v) {
        sign = 1;
        unsigned long long magnitude = static_cast<unsigned long long>(v);
        if (v < 0) {
            sign = -1;
            magnitude = 0 - magnitude;
        }
        a.clear();
        for (; magnitude > 0; magnitude /= BASE) {
            a.push_back(int(magnitude % BASE));
        }
        return *this;
    }

    BigInt& operator=(const std::string& s) {
        read(s);
        return *this;
    }

    void trim() {
        while (!a.empty() && a.back() == 0) {
            a.pop_back();
        }
        if (a.empty()) sign = 1;
    }

    void read(const std::string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -1;
            ++pos;
        }
        for (int i = int(s.size()) - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {
                x = x * 10 + (s[j] - '0');
            }
            a.push_back(x);
        }
        trim();
    }

    std::string to_string() const {
        if (a.empty()) return "0";
        std::string res = "";
        if (sign == -1) res += '-';
        res += std::to_string(a.back());
        for (int i = (int)a.size() - 2; i >= 0; --i) {
            std::string block = std::to_string(a[i]);
            res += std::string(BASE_DIGITS - block.length(), '0') + block;
        }
        return res;
    }

    bool is_zero() const {
        return a.empty() || (a.size() == 1 && a[0] == 0);
    }

    BigInt operator-() const {
        BigInt res = *this;
        if (!is_zero()) res.sign = -sign;
        return res;
    }

    BigInt abs() const {
        BigInt res = *this;
        res.sign = 1;
        return res;
    }

    friend bool operator<(const BigInt& x, const BigInt& y) {
        if (x.sign != y.sign) return x.sign < y.sign;
        if (x.a.size() != y.a.size()) {
            return (x.sign == 1) ? (x.a.size() < y.a.size()) : (x.a.size() > y.a.size());
        }
        for (int i = (int)x.a.size() - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return (x.sign == 1) ? (x.a[i] < y.a[i]) : (x.a[i] > y.a[i]);
            }
        }
        return false;
    }

    friend bool operator>(const BigInt& x, const BigInt& y) {
        return y < x;
    }
    friend bool operator<=(const BigInt& x, const BigInt& y) {
        return !(y < x);
    }
    friend bool operator>=(const BigInt& x, const BigInt& y) {
        return !(x < y);
    }
    friend bool operator==(const BigInt& x, const BigInt& y) {
        return !(x < y) && !(y < x);
    }
    friend bool operator!=(const BigInt& x, const BigInt& y) {
        return x < y || y < x;
    }

    BigInt& operator+=(const BigInt& other) {
        if (sign != other.sign) return *this -= (-other);
        for (int i = 0, carry = 0; i < (int)std::max(a.size(), other.a.size()) || carry; ++i) {
            if (i == (int)a.size()) a.push_back(0);
            a[i] += carry + (i < (int)other.a.size() ? other.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        if (sign != other.sign) return *this += (-other);
        if (abs() < other.abs()) {
            BigInt tmp = other;
            tmp -= *this;
            *this = tmp;
            sign = -sign;
            return *this;
        }
        for (int i = 0, carry = 0; i < (int)other.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int)other.a.size() ? other.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        trim();
        return *this;
    }

    BigInt& operator*=(int v) {
        long long multiplier = v;
        if (multiplier < 0) {
            sign = -sign;
            multiplier = -multiplier;
        }
        long long carry = 0;
        for (int i = 0; i < (int)a.size() || carry; ++i) {
            if (i == (int)a.size()) a.push_back(0);
            const long long cur = a[i] * multiplier + carry;
            carry = cur / BASE;
            a[i] = (int)(cur % BASE);
        }
        trim();
        return *this;
    }

    BigInt& operator*=(const BigInt& other) {
        if (is_zero() || other.is_zero()) return *this = 0;
        std::vector<int> res(a.size() + other.a.size());
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = 0, carry = 0; j < (int)other.a.size() || carry; ++j) {
                long long cur = res[i + j] + a[i] * (long long)(j < (int)other.a.size() ? other.a[j] : 0) + carry;
                carry = (int)(cur / BASE);
                res[i + j] = (int)(cur % BASE);
            }
        }
        a = res;
        sign *= other.sign;
        trim();
        return *this;
    }

    friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
        if (b1.is_zero()) {
            throw std::domain_error("BigInt division by zero");
        }
        BigInt a = a1.abs(), b = b1.abs(), q, r;
        q.a.resize(a.a.size());
        for (int i = (int)a.a.size() - 1; i >= 0; --i) {
            r *= BASE;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long)BASE * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) {
                r += b;
                --d;
            }
            q.a[i] = d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r};
    }

    BigInt& operator/=(const BigInt& other) {
        return *this = divmod(*this, other).first;
    }
    BigInt& operator%=(const BigInt& other) {
        return *this = divmod(*this, other).second;
    }

    friend BigInt operator+(BigInt x, const BigInt& y) {
        return x += y;
    }
    friend BigInt operator-(BigInt x, const BigInt& y) {
        return x -= y;
    }
    friend BigInt operator*(BigInt x, const BigInt& y) {
        return x *= y;
    }
    friend BigInt operator/(BigInt x, const BigInt& y) {
        return x /= y;
    }
    friend BigInt operator%(BigInt x, const BigInt& y) {
        return x %= y;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& b) {
        return os << b.to_string();
    }

    friend std::istream& operator>>(std::istream& is, BigInt& b) {
        std::string s;
        if (is >> s) b.read(s);
        return is;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_BIGINT_HPP
