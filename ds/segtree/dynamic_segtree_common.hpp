#ifndef M1UNE_DYNAMIC_SEGTREE_COMMON_HPP
#define M1UNE_DYNAMIC_SEGTREE_COMMON_HPP 1

#include <cassert>
#include <concepts>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {
namespace detail {

template <std::integral Index>
using dynamic_size_type = std::make_unsigned_t<Index>;

template <std::integral Index>
constexpr dynamic_size_type<Index> dynamic_distance(Index left, Index right) {
    return static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);
}

template <class Monoid, class Size>
typename Monoid::value_type monoid_repeat(typename Monoid::value_type value, Size count) {
    typename Monoid::value_type result = Monoid::id();
    while (count != 0) {
        if (count & 1) result = Monoid::op(result, value);
        count >>= 1;
        if (count != 0) value = Monoid::op(value, value);
    }
    return result;
}

template <class ActedMonoid>
typename ActedMonoid::value_type dynamic_mapping(
    const typename ActedMonoid::operator_type& f,
    const typename ActedMonoid::value_type& value
) {
    using F = typename ActedMonoid::operator_type;
    using T = typename ActedMonoid::value_type;
    if constexpr (requires(F g, T x, long long ord) { ActedMonoid::mapping(g, x, ord); }) {
        return ActedMonoid::mapping(f, value, 0);
    } else {
        return ActedMonoid::mapping(f, value);
    }
}

template <class ActedMonoid, class Size>
typename ActedMonoid::operator_type dynamic_shift(
    const typename ActedMonoid::operator_type& f,
    Size offset
) {
    using F = typename ActedMonoid::operator_type;
    if constexpr (requires(F g, long long ord) { ActedMonoid::op_shift(g, ord); }) {
        assert(offset <= static_cast<Size>(std::numeric_limits<long long>::max()));
        return ActedMonoid::op_shift(f, static_cast<long long>(offset));
    } else {
        return f;
    }
}

template <class Monoid, std::integral Index>
class UniformMonoidDomain {
   public:
    using T = typename Monoid::value_type;
    using size_type = dynamic_size_type<Index>;

   private:
    struct Level {
        size_type small_length;
        T small_value;
        T large_value;
    };

    Index _left;
    Index _right;
    T _initial_value;
    std::vector<Level> _levels;

   public:
    UniformMonoidDomain(Index left, Index right, T initial_value)
        : _left(left), _right(right), _initial_value(std::move(initial_value)) {
        assert(left <= right);
        size_type n = size();
        constexpr int digits = std::numeric_limits<size_type>::digits;
        _levels.reserve(digits + 1);
        for (int depth = 0; depth <= digits; depth++) {
            size_type small = depth == digits ? 0 : n >> depth;
            size_type large = small;
            if (depth != 0) {
                bool has_remainder;
                if (depth == digits) {
                    has_remainder = n != 0;
                } else {
                    size_type mask = (size_type(1) << depth) - 1;
                    has_remainder = (n & mask) != 0;
                }
                if (has_remainder) large++;
            }
            _levels.push_back(Level{
                small,
                monoid_repeat<Monoid>(_initial_value, small),
                monoid_repeat<Monoid>(_initial_value, large),
            });
        }
    }

    Index left_bound() const {
        return _left;
    }

    Index right_bound() const {
        return _right;
    }

    size_type size() const {
        return dynamic_distance(_left, _right);
    }

    bool empty() const {
        return _left == _right;
    }

    const T& initial_value() const {
        return _initial_value;
    }

    const T& default_product(int depth, Index left, Index right) const {
        assert(0 <= depth && depth < int(_levels.size()));
        const Level& level = _levels[depth];
        size_type length = dynamic_distance(left, right);
        if (length == level.small_length) return level.small_value;
        assert(length == level.small_length + 1);
        return level.large_value;
    }
};

}  // namespace detail
}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_SEGTREE_COMMON_HPP
