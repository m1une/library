#ifndef M1UNE_OPTIMIZATION_SLOPE_TRICK_HPP
#define M1UNE_OPTIMIZATION_SLOPE_TRICK_HPP 1

#include <cassert>
#include <functional>
#include <optional>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace optimization {

template <class T>
struct SlopeTrickArgmin {
    std::optional<T> left;
    std::optional<T> right;
};

template <class T>
class SlopeTrick {
    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);

    T _minimum = T();
    T _left_offset = T();
    T _right_offset = T();
    std::priority_queue<T> _left;
    std::priority_queue<T, std::vector<T>, std::greater<T>> _right;

    T left_top() const {
        return _left.top() + _left_offset;
    }

    T right_top() const {
        return _right.top() + _right_offset;
    }

    void push_left(T value) {
        _left.push(value - _left_offset);
    }

    void push_right(T value) {
        _right.push(value - _right_offset);
    }

   public:
    SlopeTrick() = default;

    T minimum() const {
        return _minimum;
    }

    int breakpoint_count() const {
        return int(_left.size() + _right.size());
    }

    SlopeTrickArgmin<T> argmin() const {
        SlopeTrickArgmin<T> result;
        if (!_left.empty()) result.left = left_top();
        if (!_right.empty()) result.right = right_top();
        return result;
    }

    void add_constant(T value) {
        _minimum += value;
    }

    void add_x_minus_a(T a) {
        if (!_left.empty() && left_top() > a) {
            T old = left_top();
            _minimum += old - a;
            _left.pop();
            push_left(a);
            push_right(old);
        } else {
            push_right(a);
        }
    }

    void add_a_minus_x(T a) {
        if (!_right.empty() && right_top() < a) {
            T old = right_top();
            _minimum += a - old;
            _right.pop();
            push_right(a);
            push_left(old);
        } else {
            push_left(a);
        }
    }

    void add_abs(T a) {
        add_a_minus_x(a);
        add_x_minus_a(a);
    }

    void clear_left() {
        _left = std::priority_queue<T>();
    }

    void clear_right() {
        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();
    }

    void prefix_minimum() {
        clear_right();
    }

    void suffix_minimum() {
        clear_left();
    }

    void shift(T delta) {
        _left_offset += delta;
        _right_offset += delta;
    }

    void shift(T left_delta, T right_delta) {
        assert(left_delta <= right_delta);
        _left_offset += left_delta;
        _right_offset += right_delta;
    }

    T evaluate(T x) const {
        T result = _minimum;
        auto left = _left;
        while (!left.empty()) {
            T breakpoint = left.top() + _left_offset;
            if (breakpoint > x) result += breakpoint - x;
            left.pop();
        }

        auto right = _right;
        while (!right.empty()) {
            T breakpoint = right.top() + _right_offset;
            if (x > breakpoint) result += x - breakpoint;
            right.pop();
        }
        return result;
    }

    void merge(SlopeTrick other) {
        add_constant(other._minimum);
        while (!other._left.empty()) {
            add_a_minus_x(other.left_top());
            other._left.pop();
        }
        while (!other._right.empty()) {
            add_x_minus_a(other.right_top());
            other._right.pop();
        }
    }
};

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_SLOPE_TRICK_HPP
