#ifndef M1UNE_STRING_STRING_HASH_HPP
#define M1UNE_STRING_STRING_HASH_HPP 1

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

namespace m1une {
namespace string {

struct StringHash {
    std::uint32_t first;
    std::uint32_t second;
    std::uint32_t first_power;
    std::uint32_t second_power;
    std::size_t length;

    friend constexpr bool operator==(const StringHash& left, const StringHash& right) {
        return left.length == right.length && left.first == right.first && left.second == right.second;
    }
};

namespace string_hash_detail {

inline constexpr std::uint64_t first_mod = 1'000'000'007;
inline constexpr std::uint64_t second_mod = 1'000'000'009;
inline constexpr std::uint64_t base = 911'382'323;

}  // namespace string_hash_detail

// Computes a double polynomial hash. Bytes are interpreted as unsigned.
constexpr StringHash hash_string(std::string_view value) {
    using namespace string_hash_detail;
    std::uint64_t first = 0;
    std::uint64_t second = 0;
    std::uint64_t first_power = 1;
    std::uint64_t second_power = 1;
    for (char character : value) {
        std::uint64_t symbol = static_cast<unsigned char>(character) + std::uint64_t(1);
        first = (first * base + symbol) % first_mod;
        second = (second * base + symbol) % second_mod;
        first_power = first_power * base % first_mod;
        second_power = second_power * base % second_mod;
    }
    return StringHash{
        static_cast<std::uint32_t>(first),
        static_cast<std::uint32_t>(second),
        static_cast<std::uint32_t>(first_power),
        static_cast<std::uint32_t>(second_power),
        value.size(),
    };
}

constexpr StringHash hash_string(const std::string& value) {
    return hash_string(std::string_view(value));
}

constexpr StringHash hash_string(const char* value) {
    return hash_string(std::string_view(value));
}

// Returns the hash of the concatenation represented by `left` and `right`.
constexpr StringHash concat_string_hash(const StringHash& left, const StringHash& right) {
    using namespace string_hash_detail;
    return StringHash{
        static_cast<std::uint32_t>((std::uint64_t(left.first) * right.first_power + right.first) % first_mod),
        static_cast<std::uint32_t>((std::uint64_t(left.second) * right.second_power + right.second) % second_mod),
        static_cast<std::uint32_t>(std::uint64_t(left.first_power) * right.first_power % first_mod),
        static_cast<std::uint32_t>(std::uint64_t(left.second_power) * right.second_power % second_mod),
        left.length + right.length,
    };
}

// Hash adapter for std::unordered_map and std::unordered_set.
struct StringHasher {
    using is_transparent = void;

    constexpr std::size_t operator()(std::string_view value) const {
        return operator()(hash_string(value));
    }

    constexpr std::size_t operator()(const std::string& value) const {
        return operator()(std::string_view(value));
    }

    constexpr std::size_t operator()(const char* value) const {
        return operator()(std::string_view(value));
    }

    constexpr std::size_t operator()(const StringHash& value) const {
        std::uint64_t combined = (std::uint64_t(value.first) << 32) | value.second;
        combined ^= std::uint64_t(value.length) + 0x9e3779b97f4a7c15ULL;
        combined ^= combined >> 30;
        combined *= 0xbf58476d1ce4e5b9ULL;
        combined ^= combined >> 27;
        combined *= 0x94d049bb133111ebULL;
        combined ^= combined >> 31;
        return static_cast<std::size_t>(combined);
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_STRING_HASH_HPP
