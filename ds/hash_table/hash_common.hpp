#ifndef M1UNE_HASH_COMMON_HPP
#define M1UNE_HASH_COMMON_HPP 1

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <new>
#include <type_traits>
#include <utility>

namespace m1une {
namespace ds {
namespace detail {

inline std::uint64_t splitmix64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

template <typename Key, typename Hash>
std::size_t mixed_hash(const Key& key, const Hash& hash) {
    static const std::uint64_t fixed_random =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return static_cast<std::size_t>(splitmix64(static_cast<std::uint64_t>(hash(key)) + fixed_random));
}

inline std::size_t bit_ceil(std::size_t n) {
    std::size_t result = 1;
    while (result < n) result <<= 1;
    return result;
}

inline std::size_t bucket_count_for(std::size_t expected_size) {
    return bit_ceil(std::max<std::size_t>(16, expected_size * 10 / 7 + 1));
}

template <typename T>
struct Slot {
    alignas(T) unsigned char storage[sizeof(T)];

    T* ptr() {
        return std::launder(reinterpret_cast<T*>(storage));
    }

    const T* ptr() const {
        return std::launder(reinterpret_cast<const T*>(storage));
    }

    template <typename... Args>
    void construct(Args&&... args) {
        ::new (static_cast<void*>(storage)) T(std::forward<Args>(args)...);
    }

    void destroy() {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            ptr()->~T();
        }
    }
};

}  // namespace detail
}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_HASH_COMMON_HPP
