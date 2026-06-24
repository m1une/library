#ifndef M1UNE_MATH_STERN_BROCOT_TREE_HPP
#define M1UNE_MATH_STERN_BROCOT_TREE_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

#include "rational.hpp"

namespace m1une {
namespace math {

enum class SternBrocotDirection {
    Left,
    Right,
};

struct SternBrocotRun {
    SternBrocotDirection direction;
    uint64_t count;

    friend bool operator==(const SternBrocotRun&, const SternBrocotRun&) = default;
};

struct SternBrocotPath {
    std::vector<SternBrocotRun> runs;

    bool empty() const {
        return runs.empty();
    }

    uint64_t depth() const {
        uint64_t result = 0;
        for (const SternBrocotRun& run : runs) {
            assert(run.count <= std::numeric_limits<uint64_t>::max() - result);
            result += run.count;
        }
        return result;
    }

    void push(SternBrocotDirection direction, uint64_t count = 1) {
        if (count == 0) return;
        if (!runs.empty() && runs.back().direction == direction) {
            assert(count <= std::numeric_limits<uint64_t>::max() - runs.back().count);
            runs.back().count += count;
        } else {
            runs.push_back(SternBrocotRun{direction, count});
        }
    }

    bool move_up(uint64_t count = 1) {
        if (depth() < count) return false;
        while (count > 0) {
            SternBrocotRun& run = runs.back();
            uint64_t removed = run.count < count ? run.count : count;
            run.count -= removed;
            count -= removed;
            if (run.count == 0) runs.pop_back();
        }
        return true;
    }

    SternBrocotPath ancestor(uint64_t count) const {
        SternBrocotPath result = *this;
        [[maybe_unused]] bool valid = result.move_up(count);
        assert(valid);
        return result;
    }

    friend bool operator==(const SternBrocotPath&, const SternBrocotPath&) = default;
};

template <std::signed_integral T = long long>
struct SternBrocotBounds {
    std::pair<T, T> left;
    std::pair<T, T> right;
};

template <std::signed_integral T>
SternBrocotPath stern_brocot_path(T numerator, T denominator) {
    assert(0 < numerator);
    assert(0 < denominator);
    SternBrocotPath result;
    while (numerator != denominator) {
        if (numerator < denominator) {
            T count = (denominator - 1) / numerator;
            result.push(SternBrocotDirection::Left, uint64_t(count));
            denominator -= count * numerator;
        } else {
            T count = (numerator - 1) / denominator;
            result.push(SternBrocotDirection::Right, uint64_t(count));
            numerator -= count * denominator;
        }
    }
    assert(numerator == 1);
    return result;
}

template <std::signed_integral T = long long>
Rational<T> stern_brocot_decode(const SternBrocotPath& path) {
    using Wide = __int128_t;
    Wide left_numerator = 0;
    Wide left_denominator = 1;
    Wide right_numerator = 1;
    Wide right_denominator = 0;
    Wide numerator = 1;
    Wide denominator = 1;
    [[maybe_unused]] const Wide maximum = std::numeric_limits<T>::max();
    for (const SternBrocotRun& run : path.runs) {
        assert(run.count > 0);
        assert(Wide(run.count) <= maximum);
        Wide count = run.count;
        if (run.direction == SternBrocotDirection::Left) {
            right_numerator = numerator + (count - 1) * left_numerator;
            right_denominator = denominator + (count - 1) * left_denominator;
            numerator += count * left_numerator;
            denominator += count * left_denominator;
        } else {
            left_numerator = numerator + (count - 1) * right_numerator;
            left_denominator = denominator + (count - 1) * right_denominator;
            numerator += count * right_numerator;
            denominator += count * right_denominator;
        }
        assert(numerator <= maximum);
        assert(denominator <= maximum);
        assert(left_numerator <= maximum);
        assert(left_denominator <= maximum);
        assert(right_numerator <= maximum);
        assert(right_denominator <= maximum);
    }
    return Rational<T>(T(numerator), T(denominator));
}

template <std::signed_integral T>
uint64_t stern_brocot_depth(T numerator, T denominator) {
    return stern_brocot_path(numerator, denominator).depth();
}

inline SternBrocotPath stern_brocot_lca_path(
    const SternBrocotPath& first,
    const SternBrocotPath& second
) {
    SternBrocotPath result;
    int limit = int(first.runs.size() < second.runs.size() ? first.runs.size() : second.runs.size());
    for (int i = 0; i < limit; i++) {
        if (first.runs[i].direction != second.runs[i].direction) break;
        uint64_t common =
            first.runs[i].count < second.runs[i].count
                ? first.runs[i].count
                : second.runs[i].count;
        result.push(first.runs[i].direction, common);
        if (first.runs[i].count != second.runs[i].count) break;
    }
    return result;
}

template <std::signed_integral T>
Rational<T> stern_brocot_lca(
    T first_numerator,
    T first_denominator,
    T second_numerator,
    T second_denominator
) {
    SternBrocotPath path = stern_brocot_lca_path(
        stern_brocot_path(first_numerator, first_denominator),
        stern_brocot_path(second_numerator, second_denominator)
    );
    return stern_brocot_decode<T>(path);
}

template <std::signed_integral T>
Rational<T> stern_brocot_ancestor(T numerator, T denominator, uint64_t up) {
    SternBrocotPath path = stern_brocot_path(numerator, denominator);
    [[maybe_unused]] bool valid = path.move_up(up);
    assert(valid);
    return stern_brocot_decode<T>(path);
}

template <std::signed_integral T>
Rational<T> stern_brocot_parent(T numerator, T denominator) {
    return stern_brocot_ancestor(numerator, denominator, 1);
}

template <std::signed_integral T>
Rational<T> stern_brocot_move(
    T numerator,
    T denominator,
    SternBrocotDirection direction,
    uint64_t count = 1
) {
    SternBrocotPath path = stern_brocot_path(numerator, denominator);
    path.push(direction, count);
    return stern_brocot_decode<T>(path);
}

template <std::signed_integral T = long long>
SternBrocotBounds<T> stern_brocot_bounds(const SternBrocotPath& path) {
    using Wide = __int128_t;
    Wide left_numerator = 0;
    Wide left_denominator = 1;
    Wide right_numerator = 1;
    Wide right_denominator = 0;
    Wide numerator = 1;
    Wide denominator = 1;
    [[maybe_unused]] const Wide maximum = std::numeric_limits<T>::max();

    for (const SternBrocotRun& run : path.runs) {
        assert(run.count > 0);
        assert(Wide(run.count) <= maximum);
        Wide count = run.count;
        if (run.direction == SternBrocotDirection::Left) {
            right_numerator = numerator + (count - 1) * left_numerator;
            right_denominator = denominator + (count - 1) * left_denominator;
            numerator += count * left_numerator;
            denominator += count * left_denominator;
        } else {
            left_numerator = numerator + (count - 1) * right_numerator;
            left_denominator = denominator + (count - 1) * right_denominator;
            numerator += count * right_numerator;
            denominator += count * right_denominator;
        }
        assert(numerator <= maximum);
        assert(denominator <= maximum);
        assert(left_numerator <= maximum);
        assert(left_denominator <= maximum);
        assert(right_numerator <= maximum);
        assert(right_denominator <= maximum);
    }
    SternBrocotBounds<T> result;
    result.left = {T(left_numerator), T(left_denominator)};
    result.right = {T(right_numerator), T(right_denominator)};
    return result;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_STERN_BROCOT_TREE_HPP
