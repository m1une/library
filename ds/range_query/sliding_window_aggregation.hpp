#ifndef M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_HPP
#define M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_HPP 1

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// A queue supporting the ordered product of all elements in amortized O(1).
template <m1une::monoid::IsMonoid Monoid>
struct SlidingWindowAggregation {
    using T = typename Monoid::value_type;

   private:
    struct Entry {
        T value;
        T product;
    };

    std::vector<Entry> _front;
    std::vector<Entry> _back;

    void move_to_front() {
        if (!_front.empty()) return;
        while (!_back.empty()) {
            T value = std::move(_back.back().value);
            _back.pop_back();
            T product = _front.empty() ? value : Monoid::op(value, _front.back().product);
            _front.push_back(Entry{
                std::move(value),
                std::move(product),
            });
        }
    }

   public:
    SlidingWindowAggregation() = default;

    explicit SlidingWindowAggregation(const std::vector<T>& values) {
        reserve(values.size());
        for (const T& value : values) push(value);
    }

    explicit SlidingWindowAggregation(std::vector<T>&& values) {
        reserve(values.size());
        for (T& value : values) push(std::move(value));
    }

    std::size_t size() const {
        return _front.size() + _back.size();
    }

    bool empty() const {
        return _front.empty() && _back.empty();
    }

    void reserve(std::size_t capacity) {
        _front.reserve(capacity);
        _back.reserve(capacity);
    }

    void clear() {
        _front.clear();
        _back.clear();
    }

    void push(T value) {
        T product = _back.empty() ? value : Monoid::op(_back.back().product, value);
        _back.push_back(Entry{
            std::move(value),
            std::move(product),
        });
    }

    void push_back(T value) {
        push(std::move(value));
    }

    // Removes the oldest element.
    void pop() {
        assert(!empty());
        move_to_front();
        _front.pop_back();
    }

    void pop_front() {
        pop();
    }

    const T& front() {
        assert(!empty());
        move_to_front();
        return _front.back().value;
    }

    const T& back() const {
        assert(!empty());
        if (!_back.empty()) return _back.back().value;
        return _front.front().value;
    }

    // Returns the product in queue order, or the identity when empty.
    T prod() const {
        if (_front.empty()) {
            return _back.empty() ? Monoid::id() : _back.back().product;
        }
        if (_back.empty()) return _front.back().product;
        return Monoid::op(_front.back().product, _back.back().product);
    }

    T all_prod() const {
        return prod();
    }
};

template <m1une::monoid::IsMonoid Monoid>
using Swag = SlidingWindowAggregation<Monoid>;

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_HPP
