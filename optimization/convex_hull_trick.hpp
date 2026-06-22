#ifndef M1UNE_OPTIMIZATION_CONVEX_HULL_TRICK_HPP
#define M1UNE_OPTIMIZATION_CONVEX_HULL_TRICK_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <optional>
#include <type_traits>
#include <vector>

namespace m1une {
namespace optimization {

enum class LineOptimization {
    Minimize,
    Maximize,
};

template <std::signed_integral T>
using line_wide_type = __int128_t;

template <std::signed_integral T>
struct LinearFunction {
    using value_type = line_wide_type<T>;

    value_type slope;
    value_type intercept;

    constexpr LinearFunction() : slope(0), intercept(0) {}

    constexpr LinearFunction(T slope_value, T intercept_value) : slope(slope_value), intercept(intercept_value) {}

    constexpr value_type operator()(T x) const {
        return slope * value_type(x) + intercept;
    }
};

// Convex hull trick for lines inserted in nondecreasing slope order.
template <std::signed_integral T, LineOptimization Objective = LineOptimization::Minimize>
struct ConvexHullTrick {
    using Line = LinearFunction<T>;
    using value_type = typename Line::value_type;

   private:
    std::vector<Line> _lines;

    static bool better(value_type first, value_type second) {
        if constexpr (Objective == LineOptimization::Minimize) {
            return first < second;
        } else {
            return second < first;
        }
    }

    static bool redundant(const Line& first, const Line& middle, const Line& last) {
        value_type left = (first.intercept - middle.intercept) * (last.slope - middle.slope);
        value_type right = (middle.intercept - last.intercept) * (middle.slope - first.slope);
        if constexpr (Objective == LineOptimization::Minimize) {
            return left <= right;
        } else {
            return right <= left;
        }
    }

   public:
    ConvexHullTrick() = default;

    int size() const {
        return int(_lines.size());
    }

    bool empty() const {
        return _lines.empty();
    }

    const std::vector<Line>& lines() const {
        return _lines;
    }

    void reserve(std::size_t line_capacity) {
        _lines.reserve(line_capacity);
    }

    void clear() {
        _lines.clear();
    }

    // Slopes must be inserted in nondecreasing order.
    void add_line(T slope, T intercept) {
        Line line(slope, intercept);
        if (!_lines.empty()) {
            assert(_lines.back().slope <= line.slope);
        }

        if (!_lines.empty() && _lines.back().slope == line.slope) {
            if (!better(line.intercept, _lines.back().intercept)) return;
            _lines.pop_back();
        }

        while (_lines.size() >= 2 && redundant(_lines[_lines.size() - 2], _lines.back(), line)) {
            _lines.pop_back();
        }
        _lines.push_back(line);
    }

    std::optional<value_type> try_query(T x) const {
        if (_lines.empty()) return std::nullopt;
        int low = 0;
        int high = int(_lines.size()) - 1;
        while (low < high) {
            int middle = low + (high - low) / 2;
            value_type first = _lines[middle](x);
            value_type second = _lines[middle + 1](x);
            if (better(first, second) || first == second) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        return _lines[low](x);
    }

    value_type query(T x) const {
        assert(!empty());
        return *try_query(x);
    }
};

template <std::signed_integral T>
using MinConvexHullTrick = ConvexHullTrick<T, LineOptimization::Minimize>;

template <std::signed_integral T>
using MaxConvexHullTrick = ConvexHullTrick<T, LineOptimization::Maximize>;

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_CONVEX_HULL_TRICK_HPP
