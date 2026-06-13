#ifndef M1UNE_STRING_ROLLING_HASH_HPP
#define M1UNE_STRING_ROLLING_HASH_HPP 1

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

// Standard Rolling Hash for static strings.
// Precomputes hashes to answer substring queries in O(1).
// Provides advanced operations like LCP, lexicographical comparison, and string repetition in O(log N).
template <long long Base = 10007, long long Mod = (1LL << 61) - 1>
struct RollingHash {
    std::string s;
    std::vector<long long> hash;
    std::vector<long long> power;

    RollingHash() = default;

    // Constructs the rolling hash table for the given string.
    explicit RollingHash(const std::string& str) : s(str) {
        int n = s.size();
        hash.assign(n + 1, 0);
        power.assign(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            // Use __int128_t to prevent overflow during multiplication
            hash[i + 1] = (static_cast<__int128_t>(hash[i]) * Base + s[i]) % Mod;
            power[i + 1] = (static_cast<__int128_t>(power[i]) * Base) % Mod;
        }
    }

    // Returns the hash of the substring S[l..r) in O(1).
    long long get(int l, int r) const {
        long long res = hash[r] - (static_cast<__int128_t>(hash[l]) * power[r - l]) % Mod;
        if (res < 0) res += Mod;
        return res;
    }

    // Returns the hash of the concatenated substrings S[l1..r1) and S[l2..r2).
    long long concat(int l1, int r1, int l2, int r2) const {
        long long h1 = get(l1, r1);
        long long h2 = get(l2, r2);
        return combine(h1, h2, power[r2 - l2]);
    }

    // Calculates the Longest Common Prefix (LCP) length of S[l1..r1) and S[l2..r2) in O(log N).
    int lcp(int l1, int r1, int l2, int r2) const {
        int len = std::min(r1 - l1, r2 - l2);
        int low = 0, high = len + 1;
        while (high - low > 1) {
            int mid = low + (high - low) / 2;
            if (get(l1, l1 + mid) == get(l2, l2 + mid)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low;
    }

    // Lexicographically compares S[l1..r1) and S[l2..r2) in O(log N).
    // Returns -1 if S[l1..r1) < S[l2..r2), 0 if equal, and 1 if S[l1..r1) > S[l2..r2).
    int compare(int l1, int r1, int l2, int r2) const {
        int l = lcp(l1, r1, l2, r2);
        bool end1 = (l1 + l == r1);
        bool end2 = (l2 + l == r2);
        if (end1 && end2) return 0;
        if (end1) return -1;
        if (end2) return 1;
        return s[l1 + l] < s[l2 + l] ? -1 : 1;
    }

    // Returns the hash of the substring S[l..r) repeated 'k' times.
    long long repeat(int l, int r, long long k) const {
        long long h = get(l, r);
        long long p = power[r - l];
        return repeat_hash(h, p, k);
    }

    // --- Static Helpers for dynamic processing and Monoid integration ---

    // Computes the hash of a single string in O(N) time and O(1) space.
    static long long compute_hash(const std::string& str) {
        long long h = 0;
        for (char c : str) {
            h = (static_cast<__int128_t>(h) * Base + c) % Mod;
        }
        return h;
    }

    // Combines two hashes. Equivalent to concatenating string 'b' to the right of string 'a'.
    static constexpr long long combine(long long h1, long long h2, long long base_power2) {
        return (static_cast<__int128_t>(h1) * base_power2 + h2) % Mod;
    }

    // Returns the hash of a string (with hash 'h' and base_power 'p') repeated 'k' times.
    static constexpr long long repeat_hash(long long h, long long p, long long k) {
        long long res_h = 0;
        long long res_p = 1;
        long long cur_h = h;
        long long cur_p = p;
        while (k > 0) {
            if (k & 1) {
                res_h = combine(res_h, cur_h, cur_p);
                res_p = (static_cast<__int128_t>(res_p) * cur_p) % Mod;
            }
            cur_h = combine(cur_h, cur_h, cur_p);
            cur_p = (static_cast<__int128_t>(cur_p) * cur_p) % Mod;
            k >>= 1;
        }
        return res_h;
    }

    // Creates the state pair {hash_value, base_power} for a single character.
    static constexpr std::pair<long long, long long> make_single(long long c) {
        return {c % Mod, Base % Mod};
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_ROLLING_HASH_HPP
